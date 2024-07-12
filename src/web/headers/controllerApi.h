#ifndef API_H
#define API_H

#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

void setupApi();
void handleApiClient();

extern ESP8266WebServer server;

#endif