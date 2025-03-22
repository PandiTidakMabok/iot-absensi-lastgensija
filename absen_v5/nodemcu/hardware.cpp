#include "require.hpp"

void initializeHardware() {
  Serial.println(F("====={ Inisialisasi Hardware }====="));
  setupLCD();
  setupRFID();

  WiFi.begin(config.ssid, config.password);
  http.begin(client, config.nodered);
  http.addHeader("Content-Type", "application/json");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void setupLCD() {
  Serial.print(F("* Setting Up LCD. "));
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  Serial.println(F("check"));
}

void setupRFID() {
  Serial.print(F("* Setting Up RFID. "));
  SPI.begin();

  rfid.PCD_Init();
  byte v = rfid.PCD_ReadRegister(rfid.VersionReg);
  if (v == 0x00 || v == 0xFF) {
    Serial.println(F("Failed. Not detected"));
  } else {
    Serial.println(F("check"));
  }

  Serial.print(F("RFID Version: 0x"));
  Serial.println(v, HEX);
}
