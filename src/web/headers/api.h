#include <ArduinoJson.h>
#include <WebServer.h>

void setupApi();
void handlePost();
void createJson(char *name, String value);
void addJsonObject(char *name, String value);
void getValues();
void handleClient();