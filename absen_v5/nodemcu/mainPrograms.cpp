#include "require.hpp"

volatile bool rfidFlag = false;

void setRFIDFlag() {
  rfidFlag = true;
}

void checkCard() {
  if (!rfidFlag) return;

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    rfidFlag = false;
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

  rfid.PICC_HaltA();
  rfidFlag = false;
}

void tapKartuDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tap Kartu");
}
