#include <Arduino.h>

#define ESP32_WIFI_RELAY

#include "ESPWirelessRelay.h"

void setup() {
  Serial.begin(115200);

  const char* ssid     = "Test Relay";
  const char* password = "123456789";
  const char* hostName = "testrelay.check";

  ESP32WifiRelay relay(ssid, password, hostName, 23);

  relay.begin();
  
}

void loop() {
  delay(1);
}