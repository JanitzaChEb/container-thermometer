#include "firebase.h"
#include <FirebaseESP32.h>
#include <WiFi.h>
#include "../dht/dht.h"
#include <time.h>
#include "secrets.h"

namespace DB
{

    FirebaseData fbdo;
    FirebaseJson json;
    FirebaseAuth auth;
    FirebaseConfig config;

    void syncTime()
    {
        configTime(0, 0, "pool.ntp.org", "time.nist.gov", "time.google.com");
        Serial.print("waiting for ntp");
        time_t now = time(nullptr);
        while (now < 14832)
        {
            Serial.print(".");
            delay(500);
            now = time(nullptr);
        }
        Serial.println("\ntime synchronized.");
    }

    void init()
    {
        config.api_key = Secrets::api_key;
        config.database_url = Secrets::db_url;

        auth.user.email = Secrets::user_email;
        auth.user.password = Secrets::user_pw;

        // syncTime();

        Firebase.begin(&config, &auth);
        Firebase.reconnectNetwork(true);

        fbdo.setResponseSize(4096);
        Firebase.setReadTimeout(fbdo, 15000);
        Firebase.setwriteSizeLimit(fbdo, "1MB");

        Serial.println("firebase ready");
    }

    void writeMeasurements()
    {
        FirebaseJson json;
        json.set("timestamp/.sv", "timestamp");
        json.set("temperature", Dht::temperature);
        json.set("humidity", Dht::humidity);

        if (Firebase.pushJSON(fbdo, "/readings", json))
        {
            Serial.printf("%s/%s\n", fbdo.dataPath().c_str(), fbdo.pushName().c_str());
        }
        else
        {
            Serial.printf("%s\n", fbdo.errorReason().c_str());
        }
    }
}