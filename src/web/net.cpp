#include "headers/net.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void initWifi()
{
	WiFi.begin(ssid, password);
}

void initTime()
{
	Serial.println("Time config");
	configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

	onTime.tm_hour = 7;
	onTime.tm_min = 0;

	offTime.tm_hour = 23;
	offTime.tm_min = 0;
}

bool getWifiStatus()
{
	return (WiFi.status() == WL_CONNECTED);
}

bool getTime(struct tm *timeinfo)
{
	if (!getLocalTime(timeinfo))
	{
		Serial.println("Failed to obtain time");
		return false;
	}
	return true;
}

String getLocalTimeString(const char *format)
{
	struct tm timeinfo;
	if (!getTime(&timeinfo))
	{
		return "Error";
	}

	char buffer[64];
	strftime(buffer, sizeof(buffer), format, &timeinfo);
	return String(buffer);
}
String getLocalAddress()
{
	return WiFi.localIP().toString();
}

bool isBetweenTime()
{
	struct tm timeinfo;
	if (!getTime(&timeinfo))
	{
		return false;
	}
	return ((onTime.tm_hour * 60) + onTime.tm_min < (timeinfo.tm_hour * 60) + timeinfo.tm_min) &&
			((offTime.tm_hour * 60) + offTime.tm_min > (timeinfo.tm_hour * 60) + timeinfo.tm_min);
}