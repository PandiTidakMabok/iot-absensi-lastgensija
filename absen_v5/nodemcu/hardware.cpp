#include "require.hpp"

LiquidCrystal_I2C lcd(I2CADDR, LCD_COLS, LCD_ROWS);
WiFiClient client;

void initializeHardware() {
  Serial.println(F("====={ Inisialisasi Hardware }====="));
  setupLCD();
  setupRFID();

  http.begin(client, config.nodered);
  http.addHeader("Content-Type", "application/json");

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void setupLCD() {
  Serial.print(F("* Setting Up LCD. "));
  Wire.begin(SDA_PIN, SCL_PIN);

  byte result = 0;
  Wire.beginTransmission(I2CADDR);
  result = Wire.endTransmission();
  if (result == 0) {
    Serial.println(F("check"));
  } else {
    Serial.println();
    Serial.print(F("LCD Not Found At Address 0x"));
    Serial.println(I2CADDR, HEX);
    Serial.println(F("Scaning I2C..."));
    
    for (byte address = 1; address < 127; address++) {
      Wire.beginTransmission(address);
      result = Wire.endTransmission();
      if (result == 0) {
        Serial.print(F("I2C Device Detected At 0x"));
        Serial.println(address, HEX);
        I2CADDR = address;
        lcd = LiquidCrystal_I2C(address, LCD_COLS, LCD_ROWS);
        Serial.println(F("LCD Setting Done"));
      }
    }
    
    Serial.println(F("Noting I2C device Connected"));
  }

  lcd.init();
  lcd.backlight();
  lcd.clear();
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
    Serial.print(F("RFID Version: 0x"));
    Serial.println(v, HEX);
  }

}

void restart() {
  ESP.restart();
}
