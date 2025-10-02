#include "wifi.h"
#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include <string.h>

const char* ssid = "**";
const char* password = "**";

namespace Wifi
{

    void connect(int timeout_ms)
    {
        WiFi.begin(ssid, password);

        Serial.print("connecting...");
        const int start = millis();
        while (WiFi.status() != WL_CONNECTED && (millis() - start) < timeout_ms)
        {
            delay(500);
            Serial.print(".");
        }
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("\nConnected, IP: " + WiFi.localIP().toString());
        }
        else
        {
            Serial.println("\nConnection timed out.");
        }
    }

}