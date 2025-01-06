#include "ESP32WifiRelay.h"

ESP32WifiRelay::ESP32WifiRelay(const char* ssid, const char* password, const char* hostname, int relayPin)
    : mSSID(ssid), mPassword(password), mHostname(hostname), mRelayPin(relayPin), mServer(nullptr), mWebServerTask(nullptr) {
}

ESP32WifiRelay::~ESP32WifiRelay() {
    if (mWebServerTask) {
        vTaskDelete(mWebServerTask);
        mWebServerTask = nullptr;
    }
    if (mServer) {
        mServer->stop();
        delete mServer;
        mServer = nullptr;
    }
}

void ESP32WifiRelay::handleRoot(void* instance) {
    ESP32WifiRelay* self = static_cast<ESP32WifiRelay*>(instance);
    self->mServer->send(200, "text/plain", "[ESPWifiRelay]: ok");
}

void ESP32WifiRelay::handleControl(void* instance) {
    ESP32WifiRelay* self = static_cast<ESP32WifiRelay*>(instance);
    
    if (self->mServer->hasArg("state")) {
        String state = self->mServer->arg("state");
        if (state == "high") {
            digitalWrite(self->mRelayPin, HIGH);
            self->mServer->send(200, "text/plain", "[ESPWifiRelay]: Relay ON");
        } else if (state == "low") {
            digitalWrite(self->mRelayPin, LOW);
            self->mServer->send(200, "text/plain", "[ESPWifiRelay]: Relay OFF");
        } else {
            self->mServer->send(400, "text/plain", "[ESPWifiRelay]: Invalid state value");
        }
    } else {
        self->mServer->send(400, "text/plain", "[ESPWifiRelay]: Bad Request -> 'state' parameter missing");
    }
}

void ESP32WifiRelay::begin() {
    if (mRelayPin < 0 || mRelayPin > 48 || 
        (mRelayPin >= 22 && mRelayPin <= 25) ||                                     // Reserved for SPI flash
        (mRelayPin >= 26 && mRelayPin <= 32)) {                                     // Reserved for PSRAM
        Serial.println("[ESPWifiRelay]: Invalid relay pin number!");
        return;
    }

    pinMode(mRelayPin, OUTPUT);
    digitalWrite(mRelayPin, LOW);

    WiFi.softAP(mSSID, mPassword);
    IPAddress myIP = WiFi.softAPIP();

    Serial.print("[ESPWifiRelay]: AP IP address: ");
    Serial.println(myIP);

    if (!MDNS.begin(mHostname)) {
        Serial.println("[ESPWifiRelay]: Error setting up DNS responder!");
    } else {
        Serial.println("[ESPWifiRelay]: DNS responder started");
    }

    // Create task with larger stack size and lower priority
    xTaskCreatePinnedToCore(
        webServerTask,
        "webServerTask",
        5000,        
        this,
        1,           
        &mWebServerTask,
        1            
    );
}

void ESP32WifiRelay::webServerTask(void* param) {
    ESP32WifiRelay* self = static_cast<ESP32WifiRelay*>(param);
    
    self->mServer = new WebServer(80);

    self->mServer->on("/", HTTP_GET, [self]() { handleRoot(self); });
    self->mServer->on("/control", HTTP_GET, [self]() { handleControl(self); });

    self->mServer->begin();
    Serial.println("[ESPWifiRelay]: HTTP server started");

    while (true) {
        self->mServer->handleClient();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}