#include <ArduinoJson.h>
#include <ESP8266WebServer.h>
#include <ctime>  // For time related functions
#include "headers/api.h"
#include "headers/net.h"

DynamicJsonDocument jsonDocument(1024);
char buffer[1024];
ESP8266WebServer server(80);

void setupApi()
{
  server.on("/getValues", getValues);
  server.on("/on", [](){
    displayOn = true;
    server.send(200, "application/json", "{}");
  });
  server.on("/off", [](){
    displayOn = false;
    server.send(200, "application/json", "{}");
  });
  server.on("/setStatus", HTTP_POST, handleStatusChange);
  server.on("/setTime", HTTP_POST, handleOnOffTimeChange);

  // start server
  server.begin();
}

void handleStatusChange()
{
  if (!server.hasArg("plain"))
  {
    server.send(400, "application/json", "{}");
    return;
  }
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);

  bool status = jsonDocument["status"];
  displayOn = status;
  server.send(200, "application/json", "{}");
}

void handleOnOffTimeChange()
{
  if (!server.hasArg("plain"))
  {
    server.send(400, "application/json", "{}");
    return;
  }
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);

  // Assuming onTime and offTime are strings representing time (e.g., "12:30")
  String onTime = jsonDocument["onTime"];
  String offTime = jsonDocument["offTime"];
  // Parse these strings to use as needed

  server.send(200, "application/json", "{\"timeSet\": true}");
}

void addJsonObject(const char *name, const char* value)
{
  jsonDocument[name] = value;
}

void getValues()
{
  Serial.println("Get all values");
  jsonDocument.clear(); // Clear json buffer

  // Example: Get current time as string
  char timeStr[20];
  getTimeAsString(timeStr, sizeof(timeStr));

  addJsonObject("time", timeStr);  // Example addition of time as string

  serializeJson(jsonDocument, buffer);
  server.send(200, "application/json", buffer);
}

void handleClient()
{
  server.handleClient();
}

void getTimeAsString(char* buffer, size_t bufferSize)
{
  // Example: Get current time as string
  time_t now;
  struct tm timeinfo;
  now = time(nullptr);
  localtime_r(&now, &timeinfo);
  strftime(buffer, bufferSize, "%H:%M:%S", &timeinfo);  // Format time as needed
}
