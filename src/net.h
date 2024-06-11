#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "const.h"

#ifndef NET_H
#define NET_H

void initWifi();
bool getTime(struct tm* timeinfo);
void initTime();
bool getWifiStatus();
String getLocalTimeString(const char* format);
#endif 