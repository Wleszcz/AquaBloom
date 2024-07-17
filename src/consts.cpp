#include "headers/const.h"
#include <cstdint>
#include <time.h>

//const char* ssid     = "ceska posta drti kocky";
//const char* password = "torbaborba8smake";

const char* ssid     = "WLAN1-67Q7EE";
const char* password = "happydiamond338";

const char* ntpServer = "time.google.com";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 7200;
const int APIPort = 80;

const int relays[] = {0};
bool relaysState[] = {false};

extern const int moistureSensor = 2;

const int button0 = 12;
const int button1 = 14;


const int pagesAmount = 4;
const int singleClickTime = 20; 
const int midClickTime = 700;
const int simultaneousPressThreshold = 150;

const long interval = 1000;
bool tick = false;
bool displayOn = true;

struct tm onTime = {0};
struct tm offTime = {0};

int nRelays() {
    return sizeof(relays) / sizeof(relays[0]);
}