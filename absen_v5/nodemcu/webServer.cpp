#include "HardwareSerial.h"
#include "ESP8266WiFi.h"
#include "require.hpp"

AsyncWebServer web(80);
Ticker esprestartTicker;

void initializeWebServer() {
  Serial.println(F("====={ Initialization Web Server }====="));
  Serial.print(F("* Setting up URL Routes. "));
  web.on("/", HTTP_GET, httpRoot);
  web.on("/save", HTTP_POST, httpSave);
  web.begin();
  Serial.println(F("check"));
  Serial.print(F("Web server url: http://"));
  condition.wifi ? Serial.println(WiFi.localIP()) : Serial.println(WiFi.softAPIP());
  Serial.println();
}

void httpRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", html);
}

void httpSave(AsyncWebServerRequest *request) {
  if (!request->hasArg("ssid") || !request->hasArg("password") || !request->hasArg("nodered")) {
    // Serial.println(request->arg("ssid").c_str());
    // Serial.println(request->arg("password").c_str());
    // Serial.println(request->arg("nodered").c_str());
    request->send(400, "text/plain", "Data tidak lengkap");
    Serial.println("tidak lengkap");
    return;
  }

  strlcpy(config.ssid, request->arg("ssid").c_str(), sizeof(config.ssid));
  strlcpy(config.password, request->arg("password").c_str(), sizeof(config.password));
  strlcpy(config.nodered, request->arg("nodered").c_str(), sizeof(config.nodered));

  saveConfig();

  request->send(200, "text/plain", "");

  // AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
  // response->addHeader("Location", "/");
  // request->send(response);

  esprestartTicker.once(3, restart);
}