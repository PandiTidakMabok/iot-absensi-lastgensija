#include "require.hpp"

void initializeWiFi() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");

  WiFi.begin(config.ssid, config.password);

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

void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) initializeWiFi();
}