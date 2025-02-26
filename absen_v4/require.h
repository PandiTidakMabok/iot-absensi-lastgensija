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
 * LCD I2C:
 * SDA     -> D2 (GPIO4)
 * SCL     -> D1 (GPIO5)
 * VCC     -> 5V
 * GND     -> GND
 * 
 * BUZZER:
 * Positif -> D8  (GPIO15)
 * Negatif -> GND
 */

#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "FS.h"
#include <LittleFS.h>

#ifndef require_h
#define require_h

struct Config { 
  char ssid[32];
  char password[64];
  char nodered[128];
};

#define RST_PIN D3
#define SS_PIN D4
#define SDA_PIN D2
#define SCL_PIN D1
#define NTPSERVER "0.id.pool.ntp.org"
#define BUZZER_PIN D8

const long NTPOFFSET = 7 * 3600;
const unsigned long WIFI_TIMEOUT = 10000;
const unsigned long LCD_DISPLAY_TIME = 3000;
const size_t JSON_CAPACITY = 256;
bool runprogram = false;
unsigned long lastCardTap = 0;

WiFiUDP ntpUDP;
WiFiClient client;
HTTPClient http;
Config config;

ESP8266WebServer web(80);
LiquidCrystal_I2C lcd(0x27, 20, 4);
NTPClient timeClient(ntpUDP, NTPSERVER, NTPOFFSET);
MFRC522 rfid(SS_PIN, RST_PIN);

#endif  /* require_h */