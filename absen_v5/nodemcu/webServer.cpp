#include "require.hpp"

AsyncWebServer web(80);

void initializeWebServer() {
  web.on("/", HTTP_GET, httpRoot);
  web.on("/save", HTTP_POST, httpSave);
  web.begin();
}

void httpRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", html);
}

void httpSave(AsyncWebServerRequest *request) {
  if (!request->hasArg("ssid") || !request->hasArg("password") || !request->hasArg("nodered")) {
    request->send(400, "text/plain", "Data tidak lengkap");
    return;
  }

  strlcpy(config.ssid, request->arg("ssid").c_str(), sizeof(config.ssid));
  strlcpy(config.password, request->arg("password").c_str(), sizeof(config.password));
  strlcpy(config.nodered, request->arg("mqtt").c_str(), sizeof(config.nodered));

  saveConfig();
  
  request->send(200, "text/plain", "");

  // AsyncWebServerResponse *response = request->beginResponse(302, "text/plain", "");
  // response->addHeader("Location", "/");
  // request->send(response);

  delay(1000);
  ESP.restart();
}
