#include "require.hpp"

Ticker wifiTicker;
Ticker tapKartuTicker;
Ticker rfidTicker;

void attachTicker() {
  if (!runprogram) return;
  wifiTicker.attach(10, checkWiFi);
  rfidTicker.attach(1, setRFIDFlag);
  tapKartuTicker.attach(2, tapKartuDisplay);
}

void detachTicker() {
  wifiTicker.detach();
  rfidTicker.detach();
  tapKartuTicker.detach();
}
