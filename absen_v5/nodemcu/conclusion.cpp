#include "require.hpp"

void conclusion() {
  Serial.println(F("====={ Conclusion }====="));
  if (condition.conf && condition.lcd && condition.rfid && condition.wifi) {
    Serial.println(F("All Checking are passed. you can start scanning"));
    runprogram = true;
  } else {
    Serial.println(F("Error list:"));
    if (!condition.conf) Serial.println(F("- EEPROM has empty"));
    if (!condition.lcd) Serial.println(F("- LCD not connected, check your cable"));
    if (!condition.rfid) Serial.println(F("- RFID MFRC522 not detected"));
    if (!condition.wifi) Serial.println(F("- WiFi not connected, using AP mode"));
    runprogram = false;
  }
}