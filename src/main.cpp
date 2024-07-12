#include <SPI.h>
#include <Wire.h>
#include "headers/const.h"
#include "web/headers/net.h"
#include "headers/display.h"
#include "web/headers/controllerApi.h"
#include "headers/switch.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("\n\n\n_____INITIALIZATION_____");
  if (!initDisplay())
  {
    return;
  }
  setTextAndDisplay("Connecting\n", 2, 0, 1);
  initWifi();
  int i = 0;
  while (!getWifiStatus())
  {
    setTextAndDisplay("o ", 1);
    delay(500);
    i++;
    if (i == 11)
    {
      clearDisplay();
      setTextAndDisplay("Connecting\n", 2, 0, 1);
      i = 0;
    }
  }

  clearDisplay();
  setTextAndDisplay("Connected", 2, 0, 1);
  Serial.println("WIFI connected");
  initTime();
  setupApi();
  setupGPIO();
  Serial.println("\n\n\n______WORKING______");
}

void loop()
{
  clearDisplay();

  if (displayOn && isBetweenTime())
  {
    displayWifiStatus(getWifiStatus());
    setText(getLocalTimeString(getTimeFormat()), 3, 0, 1);
    setText(getLocalTimeString("%A"), 2, 0, 25);
    setText(getLocalAddress(), 1, 0, 50);
    tick = !tick;
  }
  displayDisplay();
  handleApiClient();
  delay(1000);
}
