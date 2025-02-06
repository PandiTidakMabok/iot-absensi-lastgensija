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
  char* ssid;
  char* password;
  char* nodered;
};
#define RST_PIN D4
#define SS_PIN D3
#define SDA_PIN D2
#define SCL_PIN D1
#define NTPSERVER "0.id.pool.ntp.org"
#define NTPOFFSET 7 * 3600