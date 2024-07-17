#include "headers/gui.h"
#include "headers/const.h"
#include "headers/display.h"
#include "web/headers/net.h"
#include "headers/buttons.h"
#include "headers/page.h"
#include "headers/sensors.h"
#include <Arduino.h>

unsigned long previousMillis = 0;

bool editMode = false;
int timeDigitEdited = 0;

t_page page = MAIN_PAGE;

void updateGui()
{
    unsigned long currentMillis = millis();

    clearDisplay();

    if ((displayOn && isBetweenTime()))
    {
        switch (page.type)
        {
        case MAIN_PAGE:
            displayWifiStatus(getWifiStatus());
            setText(getLocalTimeString(getTimeFormat()), 3, 0, 1);
            setText(getLocalTimeString("%A"), 2, 0, 25);
            break;

        case PLANT_PAGE:
            setText(String(readMoistureLevel()), 2, 0 , 1);
            break;

        case ON_OFF_TIME_SET_PAGE:
            if (!editMode)
            {
                setText("ON:  " + getTimeString(onTime), 2, 0, 5);
                setText("OFF: " + getTimeString(offTime), 2, 0, 25);
            }
            else
            {
                setText("ON:", 2, 0, 5);
                setText("OFF:", 2, 0, 25);
                bool tick = (millis() % 1000) > 200;
                if (timeDigitEdited != 0 || tick)
                {
                    setText(getTimeString(onTime, "%H:"), 2, 60, 5);
                }
                if (timeDigitEdited != 1 || tick)
                {
                    setText(getTimeString(onTime, ":%M"), 2, 84, 5);
                }
                if (timeDigitEdited != 2 || tick)
                {
                    setText(getTimeString(offTime, "%H:"), 2, 60, 25);
                }
                if (timeDigitEdited != 3 || tick)
                {
                    setText(getTimeString(offTime, ":%M"), 2, 84, 25);
                }
            }
            break;

        case NET_INFO_PAGE:
            setText(getLocalAddress(), 1, 0, 45);
            break;
        }
        displayPages();
        if (currentMillis - previousMillis >= interval)
        {
            tick = !tick;
            previousMillis = currentMillis;
        }
    }
    displayDisplay();
}

void displayPages()
{
    int margin = (int)(128 - (17 * pagesAmount)) / 2;
    for (int i = 0; i < pagesAmount; i++)
    {
        if (page.page_number == i) { setText(".", 3, margin + (17 * i) - 4, 41); }
        setText("o", 2, margin + 17 * i, 50);
    }
}

void toogleEdit()
{
    timeDigitEdited = 0;
    editMode = !editMode;
}

void singleClickB0()
{
    if (!editMode)
    {
        page = (page.page_number - 1 + pagesAmount) % pagesAmount;
    }
    else if (page == ON_OFF_TIME_SET_PAGE)
    {
        editOnOffTime(-1);
    }
}

void midClickB0()
{
    if (editMode && page == ON_OFF_TIME_SET_PAGE)
    {
        timeDigitEdited = (timeDigitEdited - 1 + 4) % 4;
        Serial.println(timeDigitEdited);
    }
}

void singleClickB1()
{
    if (!editMode)
    {
        page = (page.page_number + 1) % pagesAmount;
    }
    else if (page == ON_OFF_TIME_SET_PAGE)
    {
        editOnOffTime(1);
    }
}

void midClickB1()
{
    if (editMode && page == ON_OFF_TIME_SET_PAGE)
    {
        timeDigitEdited = (timeDigitEdited + 1) % 4;
        Serial.println(timeDigitEdited);
    }
}

void editOnOffTime(int val)
{
    switch (timeDigitEdited)
    {
    case 0:
        onTime.tm_hour = abs((onTime.tm_hour + val) % 24);
        break;
    case 1:
        onTime.tm_min = abs((onTime.tm_min + val) % 60);
        break;
    case 2:
        offTime.tm_hour = abs((offTime.tm_hour + val) % 24);
        break;
    case 3:
        offTime.tm_min = abs((offTime.tm_min + val) % 64);
        break;
    }
}
