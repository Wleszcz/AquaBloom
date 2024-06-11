#include "headers/display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

static const unsigned char PROGMEM image[] = {
    0x00, 0xf0, 0x00, 0x0f, 0xff, 0x00, 0x3f, 0x0f, 0xc0, 0x78, 0x01, 0xe0, 0xe0, 0xf0, 0x70, 0x47,
    0xfe, 0x20, 0x0f, 0x9f, 0x00, 0x1c, 0x03, 0x80, 0x00, 0xf0, 0x00, 0x01, 0xfc, 0x00, 0x03, 0x9c,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00,
    0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

bool initDisplay()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println("SSD1306 allocation failed");
    return false;
  }
  Serial.println("Display initialized");
  display.clearDisplay();
  display.setTextColor(WHITE);
  return true;
}

void setText(String text, int size, int x, int y)
{
  display.setTextSize(size);
  display.setCursor(x, y);
  display.println(text);
}

void setTextAndDisplay(String text, int size)
{
  display.setTextSize(size);
  display.print(text);
  display.display();
}

void setTextAndDisplay(String text, int size, int x, int y)
{
  setText(text, size, x, y);
  display.display();
}

void displayWifiStatus(bool status)
{
  if (status || tick)
  {
    display.drawBitmap(100, 0, image, 20, 20, WHITE);
  }
  else
  {
    setText("!", 2, 105, 0);
  }
}

void clearDisplay()
{
  display.clearDisplay();
}

void displayDisplay()
{
  display.display();
}

const char *getTimeFormat()
{
  if (tick)
  {
    return "%H:%M";
  }
  else
  {
    return "%H %M";
  }
}