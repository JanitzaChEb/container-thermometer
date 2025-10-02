#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include "display/display.h"
#include "./dht/dht.h"
#include "./wifi/wifi.h"

void setup()
{
  Serial.begin(9600);
  Display::init();
  Dht::init();
  Wifi::connect(10000);
}

void loop()
{
  Display::update();
  Dht::read();
  delay(1000);
}
