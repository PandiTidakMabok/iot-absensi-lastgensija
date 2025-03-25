#include "require.hpp"

void initializeWiFi() {
  Serial.println(F("====={ Initialization WiFi }====="));
  Serial.print(F("Connecting to SSID: "));
  Serial.print(config.ssid);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  WiFi.begin(config.ssid, config.password);

  unsigned long startTime = millis();

  while (WiFi.status() != WL_CONNECTED && (millis() - startTime) < WIFI_TIMEOUT) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println(F("Failed"));
    setupAPMode();
  } else {
    Serial.println(F("check"));
    setupStationMode();
  }

  Serial.println();
}

void setupAPMode() {
  WiFi.softAP("NodeMCU", "12345678");
  Serial.println(F("AP Mode activated"));
  lcd.clear();
  lcd.print("AP Mode");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.softAPIP());
  condition.wifi = false;
}

void setupStationMode() {
  Serial.println(F("WiFi connected"));
  Serial.print(F("IP: "));
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Terkoneksi");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);

  condition.wifi = true;
}

void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) initializeWiFi();
}