#ifndef MY_DHT_H
#define MY_DHT_H

#define DHTTYPE DHT11

namespace Dht
{
    extern float temperature;
    extern float humidity;

    extern float temperature_min;
    extern float humidity_min;

    extern float temperature_max;
    extern float humidity_max;

    void init();
    void read();
}

#endif