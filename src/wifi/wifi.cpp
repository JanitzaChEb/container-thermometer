#include "wifi.h"
#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include <string.h>
#include "../secrets.h"

namespace Wifi
{

    void connect(int timeout_ms)
    {
        WiFi.begin(Secrets::ssid, Secrets::password);

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