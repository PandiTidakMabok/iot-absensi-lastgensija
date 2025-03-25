#ifndef require_hpp
#define require_hpp

#include <Wire.h>
#include <EEPROM.h>
#include <MFRC522.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <pgmspace.h>
#include <WiFiUdp.h>
#include <Ticker.h>
#include <SPI.h>

struct __attribute__((packed)) Config { 
  char ssid[32];
  char password[32];
  char nodered[128];
};
struct __attribute__((packed)) Condition {
  bool lcd;
  bool rfid;
  bool conf;
  bool wifi;
};

#define RST_PIN D3
#define SS_PIN D4
#define SDA_PIN D2
#define SCL_PIN D1
#define NTPSERVER "0.id.pool.ntp.org"
#define BUZLED_PIN D8
#define NTPOFFSET 7*3600
#define WIFI_TIMEOUT 10000
#define JSON_CAPACITY 256
#define LCD_COLS 20
#define LCD_ROWS 4

extern WiFiUDP ntpUDP;
extern WiFiClient client;
extern HTTPClient http;
extern Config config;
extern Condition condition;
extern Ticker wifiTicker;
extern Ticker rfidTicker;
extern Ticker lastTapTicker;
extern Ticker esprestartTicker;
extern Ticker tapKartuTicker;
extern Ticker buzledTicker;

extern AsyncWebServer web;
extern LiquidCrystal_I2C lcd;
extern NTPClient timeClient;
extern MFRC522 rfid;

extern bool runprogram;
extern const char html[] PROGMEM;
extern int I2CADDR;
extern volatile bool rfidFlag;
extern volatile bool buzledState;

void intro();

void initializeHardware();
void setupLCD();
void setupRFID();
void restart();

void initializeConfig();
bool setupEEPROM();
void saveConfig();

void initializeWebServer();
void httpRoot(AsyncWebServerRequest *request);
void httpSave(AsyncWebServerRequest *request);

void initializeWiFi();
void setupAPMode();
void setupStationMode();
void checkWiFi();

void conclusion();

void sendToNodered(const String& uid);
void processNodeRedResponse(const String& response);
void handleHttpError(int httpResponseCode);
void displayError(const char* message);
void setBuzledState(bool state);

void attachTicker();
void detachTicker();

void setRFIDFlag();
void checkCard();
void tapKartuDisplay();

#endif  /* require_hpp */
