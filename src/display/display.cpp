#include "display.h"
#include <Adafruit_GFX.h>
#include "../dht/dht.h"
#include "images/temperature.h"
#include "images/humidity.h"

#define SWITCH_INTERVAL_S 10

namespace Display
{

    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

    int state = TEMPERATURE;
    int updatesSinceStateSwitch = 0;

    void init()
    {
        if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        {
            Serial.println(F("SSD1306 allocation failed"));
        }
    }

    void displayTemperature() {
        display.drawBitmap(0, 0, bitmap_temperature, 128, 64, 1);

        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(5, 5);
        display.print(Dht::temperature);
        display.print(" C");
        
        // fake °
        display.setCursor(70, 3);
        display.setTextSize(1);
        display.print("o");
    }

    void displayHumidity() {
        display.drawBitmap(0, 0, bitmap_humidity, 128, 64, 1);

        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(5, 5);
        display.print(Dht::humidity);
        display.print(" %");
    }

    void displayStatistics() {
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.print("min/max values since last reboot:\n");
        display.print(Dht::humidity_min);
        display.print("% - ");
        display.print(Dht::humidity_max);
        display.print("%\n");
        display.print(Dht::temperature_min);
        display.print("C - ");
        display.print(Dht::temperature_max);
        display.print("C\n");
    }

    void update()
    {
        display.clearDisplay();
         switch (state)
            {
            case TEMPERATURE:
                displayTemperature();
                break;
            case HUMIDITY:
                displayHumidity();
                break;
            case STATISTICS:
                displayStatistics();
                break;
            default:
                break;
            }
        display.display();

        updatesSinceStateSwitch ++;
        if(updatesSinceStateSwitch > SWITCH_INTERVAL_S) {
            state++;
            if(state > 2) {
                state = 0;
            }
            updatesSinceStateSwitch = 0;
        }
    }

}