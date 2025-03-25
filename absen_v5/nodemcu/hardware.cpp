#include "require.hpp"

LiquidCrystal_I2C lcd(I2CADDR, LCD_COLS, LCD_ROWS);
MFRC522 rfid(SS_PIN, RST_PIN);

void initializeHardware() {
  Serial.println(F("====={ Initialization Hardware }====="));
  setupLCD();
  setupRFID();

  pinMode(BUZLED_PIN, OUTPUT);
  Serial.println();
}

void setupLCD() {
  Serial.print(F("* Setting Up LCD. "));
  Wire.begin(SDA_PIN, SCL_PIN);

  byte result = 0;
  Wire.beginTransmission(I2CADDR);
  result = Wire.endTransmission();
  if (result == 0) {
    Serial.println(F("check"));
    condition.lcd = true;
  } else {
    Serial.print(F("Failed. LCD Not Found At Address 0x"));
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
    
    if (result != 0) {
      Serial.println(F("Noting I2C device Connected"));
      condition.lcd = false;
    };
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
    condition.rfid = false;
  } else {
    Serial.println(F("check"));
    Serial.print(F("RFID Version: 0x"));
    Serial.println(v, HEX);
    condition.rfid = true;
  }

}

void restart() {
  ESP.restart();
}
