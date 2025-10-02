#include "dht.h"
#include <DHT.h>
#include "pins.h"

namespace Dht
{
    DHT dht(Pins::DHT, DHTTYPE);

    float temperature = 0.0f;
    float humidity = 0.0f;

    float temperature_min = 1000.0f;
    float humidity_min = 1000.0f;

    float temperature_max = 0.0f;
    float humidity_max = 0.0f;

    void init() {
        pinMode(Pins::DHT, INPUT);
        dht.begin();
    }

    void read()
    {
        Dht::humidity = dht.readHumidity();
        Dht::temperature = dht.readTemperature();

        if(Dht::humidity < Dht::humidity_min) {
            Dht::humidity_min = Dht::humidity;
        }
        if(Dht::humidity_max < Dht::humidity) {
            Dht::humidity_max = Dht::humidity;
        }

        if(Dht::temperature < Dht::temperature_min) {
            Dht::temperature_min = Dht::temperature;
        }
        if(Dht::temperature_max < Dht::temperature) {
            Dht::temperature_max = Dht::temperature;
        }
    }
}