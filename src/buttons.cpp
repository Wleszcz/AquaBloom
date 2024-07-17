#include "headers/const.h"
#include "headers/buttons.h"
#include "headers/gui.h"
#include <Arduino.h>

bool b0 = false;
bool b1 = false;

unsigned long button0PressTime = 0;
unsigned long button1PressTime = 0;

void handleButtons()
{
    unsigned long timeB0 = handleB0();
    if (timeB0 > singleClickTime && timeB0 < midClickTime)
    {
        singleClickB0();
    }
    if (timeB0 > midClickTime)
    {
        midClickB0();
    }
    
    unsigned long timeB1 = handleB1();
    if (timeB1 > singleClickTime && timeB1 < midClickTime)
    {
        singleClickB1();
    }
    if (timeB1 > midClickTime)
    {
        midClickB1();
    }

    if ((timeB0 > midClickTime || timeB1 > midClickTime) &&  abs((long)(button0PressTime - button1PressTime)) < simultaneousPressThreshold)
    {
        b0 = false;
        b1 = false;
        toogleEdit();
    }
}

unsigned long handleB0()
{
    int but0 = digitalRead(button0);
    if (!b0 && but0 == LOW)
    {
        Serial.println("BUTTON 0 PRESSED");
        b0 = true;
        button0PressTime = millis();
        delay(5);
    }
    if (b0 && but0 == HIGH)
    {
        b0 = false;
        unsigned long time = millis() - button0PressTime;
        Serial.println(time);
        return time;
    }
    return 0;
}

unsigned long handleB1()
{
    int but1 = digitalRead(button1);
    if (!b1 && but1 == LOW)
    {
        Serial.println("BUTTON 1 PRESSED");
        b1 = true;
        button1PressTime = millis();
        delay(5);
    }
    if (b1 && but1 == HIGH)
    {
        b1 = false;
        unsigned long time = millis() - button1PressTime;
        Serial.println(time);
        return time;
    }
    return 0;
}
