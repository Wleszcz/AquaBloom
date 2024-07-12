#include <ArduinoJson.h>
#include <ESP8266WebServer.h>

void setupApi();
void handleOnOffTimeChange();
void handleStatusChange();
void createJson(char *name, String value);
void addJsonObject(char *name, String value);
void getValues();
void handleClient();
void getTimeAsString(char* buffer, size_t bufferSize);