#include "headers/api.h"
#include "headers/net.h"

StaticJsonDocument<1024> jsonDocument;
char buffer[1024];
WebServer server(80);

void setupApi()
{
  server.on("/getValues", getValues);
  server.on("/on", [](){
    displayOn = true;
  });
  server.on("/off", [](){
    displayOn = false;
  });
  server.on("/setStatus", HTTP_POST, handlePost);

  // start server
  server.begin();
}

void handlePost()
{
  if (server.hasArg("plain") == false)
  {
    // handle error here
  }
  String body = server.arg("plain");
  deserializeJson(jsonDocument, body);

  displayOn = jsonDocument["status"];
  // led2Status = jsonDocument["led2Status"];

  // Respond to the client
  server.send(200, "application/json", "{}");
}

void createJson(char *name, String value)
{
  jsonDocument.clear();
  jsonDocument["name"] = name;
  jsonDocument["value"] = value;
  serializeJson(jsonDocument, buffer);
}

void addJsonObject(char *name, String value)
{
  JsonObject obj = jsonDocument.createNestedObject();
  obj["name"] = name;
  obj["value"] = value;
}

void getValues()
{
  Serial.println("Get all values");
  jsonDocument.clear(); // Clear json buffer
  addJsonObject("day", getLocalTimeString("%h"));
  addJsonObject("hour", getLocalTimeString("%h"));
  addJsonObject("min", getLocalTimeString("%m"));

  serializeJson(jsonDocument, buffer);
  server.send(200, "application/json", buffer);
}

void handleClient()
{
  server.handleClient();
}