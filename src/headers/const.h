#include <cstdint>

#ifndef CONST_H

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#define CONST_H

extern const char *ssid;
extern const char *password;
extern const char *ntpServer;
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;
extern const int APIPort;

int nRelays();
extern const int relays[];
extern bool relaysState[];

extern bool tick;
extern bool displayOn;
extern struct tm onTime;
extern struct tm offTime;
#endif