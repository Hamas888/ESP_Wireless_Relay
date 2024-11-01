 /*
 ====================================================================================================
 * File:        ESPWirlessRelay.h
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

#ifndef ESPWIRELESSRELAY_H
#define ESPWIRELESSRELAY_H


/* Includes */
#ifdef ESP32_WIFI_RELAY
#include "ESP32WifiRelay.h"
#endif

#ifdef ESP32_ESPNOW_RELAY
#endif

#ifdef ESP8226_RELAY
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#endif


// class ESPWirelessRelay {
// private:
//     const char*  mSSID;
//     const char*  mPassword;
//     const char*  mHostname;
//     int          mRelayPin;
//     TaskHandle_t mWebServerTask;

// public:
//     ESPWirelessRelay(const char* ssid, const char* password, const char* hostname, int relayPin);
//     ~ESPWirelessRelay();
//     void begin();
//     static void webServerTask(void *param);
// };

#endif // ESPWIRELESSRELAY_H