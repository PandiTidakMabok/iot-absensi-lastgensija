#include "require.h"

WiFiUDP ntpUDP;
WiFiClient client;
HTTPClient http;
Config config;
ESP8266WebServer web(80);
LiquidCrystal_I2C lcd(0x27, 20, 4);
NTPClient timeClient(ntpUDP, NTPSERVER, NTPOFFSET);
MFRC522 rfid(SS_PIN, RST_PIN);

bool runprogram = false;

void setup() {
  Serial.begin(115200);
  initializeHardware();
  setupWebServer();
  wifiConnect();
}


void loop() {
  web.handleClient(); 
  
  if (!runprogram) return;
  
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnect();
    return;
  }

    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  Serial.print("UID Card: ");
  Serial.println(uid);

  sendToNodered(uid);

  delay(1000);
  rfid.PICC_HaltA();
}

void initializeHardware() {
  EEPROM.begin(512);
  loadConfig();
  
  if (!LittleFS.begin()) {
    Serial.println(F("Failed to mount file system"));
  }
  
  Wire.begin(SDA_PIN, SCL_PIN);
  SPI.begin();
  

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  

  rfid.PCD_Init();
  

  WiFi.begin(config.ssid, config.password);
  http.begin(client, config.nodered);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
}

void setupWebServer() {
  web.on("/", HTTP_GET, httpRoot);
  web.on("/save", HTTP_POST, httpSave);
  web.begin();
}

void wifiConnect() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting to WiFi");
  
  unsigned long startTime = millis();
  
  while (WiFi.status() != WL_CONNECTED && 
         (millis() - startTime) < WIFI_TIMEOUT) {
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
  Serial.println(F("\nStarting AP Mode"));
  lcd.clear();
  lcd.print("AP Mode");
  runprogram = false;
}

void setupStationMode() {
  Serial.println(F("\nWiFi connected"));
  Serial.print(F("IP: "));
  Serial.println(WiFi.localIP());
  runprogram = true;
}

bool sendToNodered(const String& uid) {
  if (WiFi.status() != WL_CONNECTED) return false;
  
  String postData = "uid=" + uid;
  Serial.println("Sending UID: " + uid);
  
  int httpResponseCode = http.POST(postData);
  if (httpResponseCode <= 0) {
    handleHttpError(httpResponseCode);
    return false;
  }
  
  return processNodeRedResponse(http.getString());
}

bool processNodeRedResponse(const String& response) {
  DynamicJsonDocument doc(JSON_CAPACITY);
  DeserializationError error = deserializeJson(doc, response);
  
  if (error) {
    Serial.println(F("JSON parsing failed"));
    return false;
  }
  
  const char* status = doc["status"] | "failed";
  if (strcmp(status, "success") != 0) {
    displayError("Absensi Gagal");
    return false;
  }
  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(doc["nama"] | "Murid");
  lcd.setCursor(0, 1);
  lcd.print(doc["status_absen"] | "");
  
  delay(LCD_DISPLAY_TIME);
  return true;
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
}

void saveConfig() {
  EEPROM.put(0, config);
  EEPROM.commit();
}

void httpRoot() {
  File html = LittleFS.open("/index.html", "r");
  if (!html) {
    web.send(404, "text/plain", "Page not Found");
    return;
  }
  web.streamFile(html, "text/html");
  html.close();
}

void httpSave() {
  if (!web.hasArg("ssid") || !web.hasArg("password") || !web.hasArg("nodered")) {
    web.send(400, "text/plain", "Missing required fields");
    return;
  }
  
  strlcpy(config.ssid, web.arg("ssid").c_str(), sizeof(config.ssid));
  strlcpy(config.password, web.arg("password").c_str(), sizeof(config.password));
  strlcpy(config.nodered, web.arg("nodered").c_str(), sizeof(config.nodered));
  
  saveConfig();
  
  web.sendHeader("Location", "/");
  web.send(302, "text/plain", "");
  ESP.restart();
}