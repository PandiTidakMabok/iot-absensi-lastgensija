#include "require.hpp"

Ticker wifiTicker;
Ticker rfidTicker;

void attachTicker() {
  if (!runprogram) return;
  wifiTicker.attach(10, checkWiFi);
  rfidTicker.attach(1, checkCard);
}

void detachTicker() {
  wifiTicker.detach();
  rfidTicker.detach();
}