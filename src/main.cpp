#include <Arduino.h>

#define ESP32_WIFI_RELAY

#include "ESPWirelessRelay.h"

ESP32WifiRelay* relay = nullptr;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(100);
  }
  
  const char* ssid      = "Test Relay";
  const char* password  = "123456789";
  const char* hostName  = "testrelay.local";
  
  relay = new ESP32WifiRelay(ssid, password, hostName, 2);
  relay->begin();
}

void loop() {
  delay(1);
}