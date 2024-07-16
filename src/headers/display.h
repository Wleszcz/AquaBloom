#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "headers/const.h"

#ifndef DISPLAY_H
#define DISPLAY_H
bool initDisplay();
void setText(String text, int size, int x, int y);
void setTextAndDisplay(String text, int size);
void setTextAndDisplay(String text, int size, int x, int y);
void displayWifiStatus(bool status);
void clearDisplay();
void displayDisplay();
const char *getTimeFormat();
String getTimeString(struct tm time);
#endif