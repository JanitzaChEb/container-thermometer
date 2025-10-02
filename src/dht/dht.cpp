#include "dht.h"
#include <DHT.h>
#include "pins.h"

namespace Dht
{
    DHT dht(Pins::DHT, DHTTYPE);

    float temperature = 0.0f;
    float humidity = 0.0f;

    void init() {
        pinMode(Pins::DHT, INPUT);
        dht.begin();
    }

    void read()
    {
        Dht::humidity = dht.readHumidity();
        Dht::temperature = dht.readTemperature();
    }
}