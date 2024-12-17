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

// Pin Konfigurasi
#define RST_PIN D1
#define SS_PIN D2

// Konfigurasi WiFi
const char* ssid = "Grendel International";
const char* password = "";

// Konfigurasi Server Database
const char* getData = "http://192.168.20.250/absensi/get_data.php";
const char* nodered = "http://192.168.20.250:1880/absensi";

// Konfigurasi NTP
const char* ntpServer = "0.id.pool.ntp.org";
const int ntpOffset = 7 * 3600;