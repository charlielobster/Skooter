#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID 
#define STAPSK  "SuperSecurePassword@Physics421"
#endif

#include "Espy.h"

Espy e;

static const String ssid = "CCNYPhysicsClub_2.4";
static const String password = "SuperSecurePassword@Physics421";
  
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  Serial.begin(74880);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("using ssid: " + ssid + " " + password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  e.setup();
  Serial.println("HTTP server started");
}

void loop() {
  e.loop();
  MDNS.update();
}
