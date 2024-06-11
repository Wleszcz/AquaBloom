#include <SPI.h>
#include <Wire.h>
#include "const.h"
#include "net.h"
#include "display.h"

void setup() {
  Serial.begin(115200);
  if (!initDisplay()) {
    return;
  }
  setTextAndDisplay("Connecting\n", 2, 0, 1);
  initWifi();
  int i = 0;
  while (!getWifiStatus()) {
    setTextAndDisplay("o ", 1);
    delay(500);
    i++;
    if (i == 11) {
      clearDisplay();
      setTextAndDisplay("Connecting\n", 2, 0, 1);
      i=0;
    }
  }
  
  clearDisplay();
  setTextAndDisplay("Connected", 2, 0, 1);
  initTime();
  
}

void loop() {
  clearDisplay();

  displayWifiStatus(getWifiStatus());
  setText(getLocalTimeString(getTimeFormat()),3 , 0, 1);
  setTextAndDisplay(getLocalTimeString("%A"),2 , 0, 25);
  tick = !tick;
  delay(1000);
}

