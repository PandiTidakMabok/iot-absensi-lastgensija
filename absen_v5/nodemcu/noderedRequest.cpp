#include "require.hpp"

WiFiClient client;
HTTPClient http;
Ticker lastTapTicker;
Ticker buzledTicker;
volatile bool buzledState = false;

void sendToNodered(const String& uid) {
  checkWiFi();

  DynamicJsonDocument doc(200);
  doc["uid"] = uid;

  String jsonData;
  serializeJson(doc, jsonData);

  Serial.println("Mengirim JSON: " + jsonData);

  http.begin(client, config.nodered);
  http.addHeader("Content-Type", "application/json");
  http.setTimeout(5000);
  int httpResponseCode = http.POST(jsonData);

  if (httpResponseCode <= 0) {
    handleHttpError(httpResponseCode);
    return;
  }
  processNodeRedResponse(http.getString());
  http.end();
}

void processNodeRedResponse(const String& response) {
  DynamicJsonDocument doc(512);
  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    Serial.println(F("JSON parsing gagal"));
    return;
  }

  const char* status = doc["status"] | "failed";
  if (strcmp(status, "success") != 0) {
    displayError("Absensi Gagal");
    setBuzledState(true);
    buzledTicker.once(1, setBuzledState, false);
    lastTapTicker.once(2, attachTicker);
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(doc["nama"] | "Murid");
  lcd.setCursor(0, 1);
  lcd.print(doc["status_absen"] | "");

  setBuzledState(true);
  buzledTicker.once_ms(500, setBuzledState, false);
  lastTapTicker.once(2, attachTicker);
  http.end();
  return;
}

void handleHttpError(int httpResponseCode) {
  Serial.print("HTTP Error: ");
  Serial.println(httpResponseCode);
  displayError("Koneksi Error");
}

void displayError(const char* message) {
  lcd.clear();
  lcd.print(message);
  delay(2000);
}

void setBuzledState(bool state) {
  buzledState = state ? HIGH : LOW;
  digitalWrite(BUZLED_PIN, buzledState);
}