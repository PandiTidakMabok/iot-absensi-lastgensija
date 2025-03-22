#include "require.hpp"

void checkCard() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tap Kartu");

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  detachTicker();

  String uid = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uid += String(rfid.uid.uidByte[i], HEX);
  }

  Serial.print("UID Card: ");
  Serial.println(uid);

  sendToNodered(uid);

  delay(50);
  rfid.PICC_HaltA();
}