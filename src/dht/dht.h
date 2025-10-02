#ifndef MY_DHT_H
#define MY_DHT_H

#define DHTTYPE DHT11

namespace Dht
{
    extern float temperature;
    extern float humidity;

    void init();
    void read();
}

#endif