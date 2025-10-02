#ifndef MY_DISPLAY_H
#define MY_DISPLAY_H

#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

namespace Display
{

    enum State
    {
        TEMPERATURE = 0,
        HUMIDITY = 1
    };

    extern Adafruit_SSD1306 display;
    extern State state;

    void init();
    void update();
}

#endif