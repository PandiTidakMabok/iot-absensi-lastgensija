#include "require.hpp"

Config config;

void initializeConfig() {
  Serial.println(F("====={ Initialization Configuration }====="));
  bool state = setupEEPROM();
  if (!state) return;
  Serial.println(F("Loaded config: "));
  Serial.print(F("- SSID: "));
  Serial.println(config.ssid);
  Serial.print(F("- Password: "));
  Serial.println(config.password);
  Serial.print(F("- Node-RED: "));
  Serial.println(config.nodered);
  Serial.println();
}

bool setupEEPROM() {
  Serial.print(F("* Setting Up EEPROM. "));
  EEPROM.begin(512);
  EEPROM.get(0, config);
  if (strlen(config.ssid) > 0 && strlen(config.password) > 0 && strlen(config.nodered) > 0) {
    Serial.println(F("check"));
    condition.conf = true;
    return true;
  } else {
    Serial.println(F("Failed"));
    condition.conf = false;
    return false;
  }
}

void saveConfig() {
  EEPROM.put(0, config);
  bool success = EEPROM.commit();

  if (!success) {
    Serial.println(F("Gagal menyimpan konfigurasi"));
    return;
  }

  Serial.println(F("Konfigurasi berhasil disimpan"));
}