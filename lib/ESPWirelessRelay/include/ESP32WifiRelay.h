 /*
 ====================================================================================================
 * File:        ESP32WifiRelay.h
 * Author:      Hamas Saeed
 * Version:     Rev_1.0.0
 * Date:        March 10, 2024
 * Brief:       
 * 
 ====================================================================================================
 * License: 
 * This file is licensed under the GNU Affero General Public License (AGPL) v3.0.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 * https://www.gnu.org/licenses/agpl-3.0.en.html
 * 
 * Commercial licensing: For commercial use of this software, please contact Hamas Saeed at 
 * hamasaeed@gmail.com.
 * 
 * Distributed under the AGPLv3 License. Software is provided "AS IS," without any warranties 
 * or conditions of any kind, either express or implied.
 *
 =====================================================================================================
 */

#ifndef ESP32WIFIRELAY_H
#define ESP32WIFIRELAY_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>


class ESP32WifiRelay {
private:
    const char*  mSSID;
    const char*  mPassword;
    const char*  mHostname;
    int          mRelayPin;
    TaskHandle_t mWebServerTask;

public:
    ESP32WifiRelay(const char* ssid, const char* password, const char* hostname, int relayPin);
    ~ESP32WifiRelay();
    void begin();
    static void webServerTask(void *param);
};


#endif // ESP32WIFIRELAY_H