#include "require.h"

WiFiUDP ntpUDP;
WiFiClient client;
HTTPClient http;
Config config;

ESP8266WebServer web(80);
LiquidCrystal_I2C lcd(0x27, 20, 4);
NTPClient timeClient(ntpUDP, NTPSERVER, NTPOFFSET);
MFRC522 rfid(SS_PIN, RST_PIN);

bool runprogram;

void setup() {
  Serial.begin(115200);
  EEPROM.begin(512);
  loadConfig();
  LittleFS.begin();
  WiFi.begin();
  Wire.begin(SDA_PIN, SCL_PIN);
  web.begin();
  SPI.begin();
  http.begin(client, config.nodered);
  lcd.init();
  rfid.PCD_Init();

  lcd.backlight();
  lcd.clear();

  wifiConnect()

  web.on("/", HTTP_GET, httpRoot);
  web.on("/save", HTTP_POST, httpSave);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
}

void loop() {
  if (runprogram) {
    if (WiFi.status() == WL_CONNECTED) {
      
    } else {
      wifiConnect();
    }
  }
}

void wifiConnect() {
  lcd.setCursor(0, 0);
  lcd.print("Conneting to WiFi");
  unsigned long startWiFiAtempt = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - startWiFiAtempt) >= 10000) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.softAP("NodeMCU", "12345678");
    Serial.println("");
    Serial.println("Failed to Connect");
    lcd.print("AP Mode");
    runprogram = false;
  } else {
    Serial.println("");
    Serial.print("Connected to WiFi. IP: ");
    Serial.println(WiFi.localIP());
    runprogram = true;
  }
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
  String ssid = web.arg("ssid");
  String password = web.arg("password");
  String nodered = web.arg('nodered');
  
  strlcpy(config.ssid, ssid.c_str(), sizeof(config.ssid));
  strlcpy(config.password, password.c_str(), sizeof(config.password));
  strlcpy(config.nodered, nodered.c_str(), sizeof(config.nodered));
  saveConfig();

  web.send(200, "text/plain", "")
  web.sendHeader("Location", "/");
  web.send(302, "text/plain", "");
  ESP.restart();
}

bool sendToNodered(String uid) {
  if (WiFi.status() == WL_CONNECTED) {

    String postData = "uid=" + uid;

    Serial.print("Sending UID to Node-RED: ");
    Serial.println(uid);

    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Node-RED Response: " + response);

      DynamicJsonDocument doc(256);
      DeserializationError error = deserializeJson(doc, response);

      if (!error) {
        const char* status = doc["status"] | "Gagal";

        if (strcmp(status, "success") == 0) {
          const char* nama = doc["nama"] | "Murid";
          const char* kelas = doc["kelas"] | "";
          const char* status_absen = doc["status_absen"] | "";

          timeClient.update();
          int currentHour = timeClient.getHours();
          int currentMinute = timeClient.getMinutes();

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(nama);
          lcd.setCursor(0, 1);
          lcd.print(status_absen);

          delay(3000);

          return true;
        } else {
          lcd.clear();
          lcd.print("Absensi Gagal");
          delay(2000);
        }
      }
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);

      lcd.clear();
      lcd.print("Koneksi Error");
      delay(2000);
    }

    http.end();
    http.end();
  }
  return false;
}