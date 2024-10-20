#include <Arduino.h>
#include "ESPWirelessRelay.h"

void setup() {
  Serial.begin(115200);

  const char* ssid     = "Test Relay";
  const char* password = "123456789";
  const char* hostName = "testrelay.check";

  ESPWirelessRelay relay(ssid, password, hostName, 5);

  relay.begin();
  
}

void loop() {
  delay(1);
}