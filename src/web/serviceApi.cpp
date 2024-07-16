#include "headers/serviceApi.h"
#include "headers/controllerApi.h"
#include "../headers/const.h"
#include <ArduinoJson.h>
#include "pages/headers/mainPage.h"
#include "../headers/switch.h"

DynamicJsonDocument jsonDocument(1024);
char buffer[1024];

void handleLandingPage()
{
    Serial.println("Handling request");
    // Send the HTML page

    String dynamicContent;

    // Generate buttons for each relay
    for (int i = 0; i < nRelays(); ++i)
    {
        dynamicContent += "<p class='relay-label'>Relay " + String(i) + ":</p>";
        if (!relaysState[i])
        {
            dynamicContent += "<button class='button' onclick=\"sendPost(" + String(relays[i]) + ", true)\">ON</button>";
        }
        if (relaysState[i])
        {
            dynamicContent += "<button class='button' onclick=\"sendPost(" + String(relays[i]) + ", false)\">OFF</button>";
        }
    }
    dynamicContent += String(buttonScript);
    dynamicContent += "</body></html>";

    // Concatenate the static and dynamic parts of the HTML content
    String finalPageContent = String(mainPageContent) + dynamicContent;
    char *pageContent = const_cast<char *>(finalPageContent.c_str());

    // Send the HTML page
    server.send(200, "text/html", pageContent);
}

void handleRelayChange()
{
    DeserializationError error = deserializeJson(jsonDocument, server.arg("plain"));
    if (error)
    {
        server.send(400, "application/json", "{\"error\": \"Failed to parse JSON\"}");
        return;
    }

    // Extract values from JSON document
    int pin = jsonDocument["pin"].as<int>();
    bool state = jsonDocument["state"].as<bool>();

    // Call the method to control the relay
    controlRelay(pin, state);

    // Send response
    server.send(200, "application/json", "{\"message\": \"Relay state changed\"}");
}

void handleGetTime() {
    StaticJsonDocument<200> doc;
    doc["onTime"]["hour"] = onTime.tm_hour;
    doc["onTime"]["minute"] = onTime.tm_min;
    doc["offTime"]["hour"] = offTime.tm_hour;
    doc["offTime"]["minute"] = offTime.tm_min;

    String response;
    serializeJson(doc, response);
    server.send(200, "application/json", response);
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
    if (server.hasArg("plain") == false) { // Check if the body is available
    server.send(400, "application/json", "{\"error\":\"Bad Request\"}");
    return;
  }

  String body = server.arg("plain");
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, body);

  if (error) {
    server.send(400, "application/json", "{\"error\":\"Invalid JSON\"}");
    return;
  }

  // Assuming the JSON structure is {"onTime": {"hour": 7, "minute": 0}, "offTime": {"hour": 23, "minute": 0}}
  if (doc.containsKey("onTime") && doc.containsKey("offTime")) {
    onTime.tm_hour = doc["onTime"]["hour"];
    onTime.tm_min = doc["onTime"]["minute"];
    offTime.tm_hour = doc["offTime"]["hour"];
    offTime.tm_min = doc["offTime"]["minute"];

    server.send(200, "application/json", "{\"message\":\"Times updated successfully\"}");
  } else {
    server.send(400, "application/json", "{\"error\":\"Missing required fields\"}");
  }
}

void addJsonObject(const char *name, const char *value)
{
    jsonDocument[name] = value;
}
void handleClient()
{
    server.handleClient();
}
