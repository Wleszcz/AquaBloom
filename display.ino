#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "const.h"


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void printText(String text, int size, int x, int y);
bool getTime(struct tm* timeinfo);
String getLocalTimeString(const char* format);

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  printText("Connecting", 2, 0, 1);
display.display();

  WiFi.begin(ssid, password);
  int i=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    printText(".", 2, 4 * i++, 25);
    display.display();
   }
  display.clearDisplay();
  display.display();

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

void loop() {
  
  display.clearDisplay();
  if (tak) {
    printText(getLocalTimeString("%H:%M"),3 , 0, 1);
  }
  else{
    printText(getLocalTimeString("%H %M"),3 , 0, 1);
  }
  tak = !tak;
  printText(getLocalTimeString("%A"),2 , 0, 25);
  display.display();
  delay(1000);
}


void printText(String text, int size, int x, int y) {
  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.println(text);
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



