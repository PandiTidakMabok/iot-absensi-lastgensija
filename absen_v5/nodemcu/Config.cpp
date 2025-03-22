#include "require.hpp"

Config config;

void initializeConfig() {
  Serial.println(F("====={ Inisialisasi Konfigurasi }====="));
  setupEEPROM();
  Serial.println(F("Loaded config: "));
  Serial.print(F("\t SSID: "));
  Serial.println(config.ssid);
  Serial.print(F("\t Password: "));
  Serial.println(config.password);
  Serial.print(F("\t Node-RED: "));
  Serial.println(config.nodered);
  Serial.println();
}

void setupEEPROM() {
  Serial.print(F("* Setting Up EEPROM"));
  EEPROM.begin(512);
  EEPROM.get(0, config);
  Serial.println(F("check"));
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