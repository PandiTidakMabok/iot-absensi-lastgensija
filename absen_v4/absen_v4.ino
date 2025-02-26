#include "require.h"

void setup() {
  Serial.begin(115200);
  initializeHardware();
  delay(100);
  setupWebServer();
  delay(100);
  wifiConnect();
}

void loop() {
  web.handleClient();

  if (!runprogram) {
    delay(10);
    return;
  }

  if (millis() - lastCardTap > 2000) {
    static unsigned long lastDisplay = 0;
    if (millis() - lastDisplay > 1000) {
      lastDisplay = millis();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Tap Kartu");
    }
  }

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  lastCardTap = millis();

  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  Serial.print("UID Card: ");
  Serial.println(uid);

  sendToNodered(uid);

  delay(50);
  rfid.PICC_HaltA();
}

void initializeHardware() {
  Serial.println("Inisialisasi Hardware");
  EEPROM.begin(512);
  loadConfig();

  if (!LittleFS.begin()) {
    Serial.println("Gagal mount file system");
  }

  Wire.begin(SDA_PIN, SCL_PIN);
  SPI.begin();

  lcd.init();
  lcd.backlight();
  lcd.clear();

  rfid.PCD_Init();
  byte v = rfid.PCD_ReadRegister(rfid.VersionReg);
  Serial.print("RFID Version: 0x");
  Serial.println(v, HEX);
  if (v == 0x00 || v == 0xFF) {
    Serial.println("Warning: RFID reader tidak terdeteksi!");
  }

  WiFi.begin(config.ssid, config.password);
  http.begin(client, config.nodered);
  http.addHeader("Content-Type", "application/json");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void setupWebServer() {
  web.begin();
  web.on("/", HTTP_GET, httpRoot);
  web.on("/save", HTTP_POST, httpSave);
}

void wifiConnect() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED && (millis() - startTime) < WIFI_TIMEOUT) {
    delay(250);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    setupAPMode();
  } else {
    setupStationMode();
  }
}

void setupAPMode() {
  WiFi.softAP("NodeMCU", "12345678");
  Serial.println(F("\nAP Mode Aktif"));
  lcd.clear();
  lcd.print("AP Mode");
  runprogram = false;
}

void setupStationMode() {
  Serial.println(F("\nWiFi Terkoneksi"));
  Serial.print(F("IP: "));
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Terkoneksi");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);

  runprogram = true;
}

void sendToNodered(const String& uid) {
  if (WiFi.status() != WL_CONNECTED) return;

  DynamicJsonDocument doc(200);
  doc["uid"] = uid;

  String jsonData;
  serializeJson(doc, jsonData);

  Serial.println("Mengirim JSON: " + jsonData);

  http.setTimeout(5000);
  int httpResponseCode = http.POST(jsonData);

  if (httpResponseCode <= 0) {
    handleHttpError(httpResponseCode);
    return;
  }

  processNodeRedResponse(http.getString());
}

void processNodeRedResponse(const String& response) {
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.println(F("JSON parsing gagal"));
    return;
  }

  const char* status = doc["status"] | "failed";
  if (strcmp(status, "success") != 0) {
    displayError("Absensi Gagal");
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(doc["nama"] | "Murid");
  lcd.setCursor(0, 1);
  lcd.print(doc["status_absen"] | "");

  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  delay(LCD_DISPLAY_TIME);
  return;
}

void handleHttpError(int httpResponseCode) {
  Serial.print("HTTP Error: ");
  Serial.println(httpResponseCode);
  displayError("Koneksi Error");
}

void displayError(const char* message) {
  lcd.clear();
  lcd.print(message);
  delay(2000);
}

void loadConfig() {
  EEPROM.get(0, config);
  Serial.println("Loaded config:");
  Serial.println(config.ssid);
  Serial.println(config.password);
  Serial.println(config.nodered);
}

void saveConfig() {
  EEPROM.put(0, config);
  bool success = EEPROM.commit();

  if (!success) {
    Serial.println("Gagal menyimpan konfigurasi");
    return;
  }

  Serial.println("Konfigurasi berhasil disimpan");
}

void httpRoot() {
  File html = LittleFS.open("/index.html", "r");
  if (!html) {
    web.send(404, "text/plain", "Halaman Tidak Ditemukan");
    return;
  }
  web.streamFile(html, "text/html");
  html.close();
}

void httpSave() {
  if (!web.hasArg("ssid") || !web.hasArg("password") || !web.hasArg("nodered")) {
    web.send(400, "text/plain", "Data tidak lengkap");
    return;
  }

  strlcpy(config.ssid, web.arg("ssid").c_str(), sizeof(config.ssid));
  strlcpy(config.password, web.arg("password").c_str(), sizeof(config.password));
  strlcpy(config.nodered, web.arg("nodered").c_str(), sizeof(config.nodered));

  saveConfig();

  web.send(200, "text/plain", "");
  web.sendHeader("Location", "/");
  web.send(302, "text/plain", "");

  delay(1000);
  ESP.restart();
}
