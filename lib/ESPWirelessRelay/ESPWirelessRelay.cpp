#include "ESPWirelessRelay.h"


ESPWirelessRelay::ESPWirelessRelay(const char* ssid, const char* password, const char* hostname, int relayPin) 
: mSSID(ssid), mPassword(password), mHostname(hostname), mRelayPin(relayPin) {
}

ESPWirelessRelay::~ESPWirelessRelay() {

}

void ESPWirelessRelay::begin() {
    pinMode(mRelayPin, OUTPUT);
    digitalWrite(mRelayPin, LOW);

#ifdef ESP32_RELAY
    WiFi.softAP(mSSID, mPassword, true);                                                         // Creating Access Point
    IPAddress myIP = WiFi.softAPIP();

    Serial.print("- ESPWirelessRelay Logs -> AP IP address: ");
    Serial.println(myIP);


    if (!MDNS.begin(mHostname)) {                                                                // Configuring DNS Responder
        Serial.println("- ESPWirelessRelay Logs -> Error setting up DNS responder!");
    } else {
        Serial.println("- ESPWirelessRelay Logs -> DNS responder started");
    }

    xTaskCreate(
        webServerTask,
        "webServerTask",
        5000,
        this, 
        28,
        &mWebServerTask
    );
#endif
}

void ESPWirelessRelay::webServerTask(void *param) {
#ifdef ESP32_RELAY
    ESPWirelessRelay* self = static_cast<ESPWirelessRelay*>(param);
    static WebServer server(80);

    server.on("/", HTTP_GET, []() {                                                             
        server.send(200, "text/plain", "espRelay1 check: ok");
    });

    server.on("/control", HTTP_GET, [self](){  // Capture 'self' to access member variables
        if (server.hasArg("state")) {
            String state = server.arg("state");
            if (state == "high") {
                digitalWrite(self->mRelayPin, HIGH);
            } else if (state == "low") {
                digitalWrite(self->mRelayPin, LOW);
            }
            server.send(200, "text/plain", "OK");
        } else {
            server.send(400, "text/plain", "Bad Request: 'state' parameter missing");
        }
    });

    server.begin();                                                                             

    while(true) {
        server.handleClient();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
#endif
}



