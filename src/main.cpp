#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "display/display.h"
#include "./dht/dht.h"

void setup()
{
  Display::init();
  Dht::init();
}

void loop()
{
  Display::update();
  Dht::read();
  delay(1000);
}
