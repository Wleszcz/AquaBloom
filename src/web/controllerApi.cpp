#include <ESP8266WebServer.h>
#include "headers/controllerApi.h"
#include "headers/net.h"
#include "headers/serviceApi.h"
#include "../headers/switch.h"

ESP8266WebServer server(APIPort);

void setupApi()
{
  server.on("/", HTTP_GET, handleLandingPage);
  server.on("/on", []()
            {
    displayOn = true;
    server.send(200, "application/json", "Turning on"); });
  server.on("/off", []()
            {
    displayOn = false;
    server.send(200, "application/json", "Turning off"); });
  server.on("/getTime", HTTP_GET, handleGetTime);

  server.on("/relays", HTTP_POST, handleRelayChange);
  server.on("/setStatus", HTTP_POST, handleStatusChange);
  server.on("/setTime", HTTP_POST, handleOnOffTimeChange);

  // start server
  server.begin();
  Serial.println("API started");
}

void handleApiClient()
{
  handleClient();
}
