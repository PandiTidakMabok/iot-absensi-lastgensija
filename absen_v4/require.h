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

const long NTPOFFSET = 7 * 3600;
const unsigned long WIFI_TIMEOUT = 10000; 
const unsigned long LCD_DISPLAY_TIME = 3000; 
const size_t JSON_CAPACITY = 256;