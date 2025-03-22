#include "require.hpp"

HTTPClient http;
Ticker lastTapTicker;

void sendToNodered(const String& uid) {
  if (WiFi.status() != WL_CONNECTED) return;

  DynamicJsonDocument doc(200);
  doc["uid"] = uid;

  String jsonData;
  serializeJson(doc, jsonData);

  Serial.println("Mengirim JSON: " + jsonData);

  http.setTimeout(5000);
  int httpResponseCode = http.POST(jsonData);

  if (httpResponseCode <= 0) {
    handleHttpError(httpResponseCode);
    return;
  }

  processNodeRedResponse(http.getString());
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
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(doc["nama"] | "Murid");
  lcd.setCursor(0, 1);
  lcd.print(doc["status_absen"] | "");

  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);

  lastTapTicker.once(2, attachTicker);
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