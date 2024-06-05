#include "net.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void initWifi() {
  WiFi.begin(ssid, password);
}

void initTime() {
  Serial.println("Time config");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

bool getWifiStatus() {
  return (WiFi.status() == WL_CONNECTED);
}

bool getTime(struct tm* timeinfo) {
    if (!getLocalTime(timeinfo)) {
        Serial.println("Failed to obtain time");
        return false;
    }
    return true;
}

String getLocalTimeString(const char* format) {
    struct tm timeinfo;
    if (!getTime(&timeinfo)) {
        return "Error";
    }

    char buffer[64];
    strftime(buffer, sizeof(buffer), format, &timeinfo);
    return String(buffer);
}