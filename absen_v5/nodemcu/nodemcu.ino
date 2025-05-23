/* 
 * NodeMCU Pin Configuration
 * 
 * RFID MFRC522:
 * RST     -> D3 (GPIO0)
 * MISO    -> D6 (GPIO12)
 * MOSI    -> D7 (GPIO13)
 * SCK     -> D5 (GPIO14)
 * SDA/SS  -> D4 (GPIO2)
 * 3.3V    -> 3.3V
 * GND     -> GND
 * 
 * LCD I2C 20x4:
 * SDA     -> D2 (GPIO4)
 * SCL     -> D1 (GPIO5)
 * VCC     -> 3.3V (5V highly recommended)
 * GND     -> GND
 * 
 * BUZZER/LED:
 * Positif -> D8 (GPIO15)
 * Negatif -> GND
 */

#include "require.hpp"

void setup() {
  delay(1000);
  Serial.begin(115200);
  intro();
  initializeHardware();
  initializeConfig();
  initializeWiFi();
  initializeWebServer();
  conclusion();
  attachTicker();
}

void loop() {
  checkCard();
  yield();
}
