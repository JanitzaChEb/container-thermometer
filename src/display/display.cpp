#include "display.h"
#include <Adafruit_GFX.h>
#include "../dht/dht.h"

#define SWITCH_INTERVAL_S 10

namespace Display
{

    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

    State state = TEMPERATURE;
    int updatesSinceStateSwitch = 0;

    void init()
    {
        if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
        {
            Serial.println(F("SSD1306 allocation failed"));
        }
    }

    void displayTemperature() {
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
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(5, 5);
        display.print(Dht::humidity);
        display.print(" %");
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
            default:
                break;
            }
        display.display();

        updatesSinceStateSwitch ++;
        if(updatesSinceStateSwitch > SWITCH_INTERVAL_S) {
            state = state == TEMPERATURE ? HUMIDITY : TEMPERATURE;
            updatesSinceStateSwitch = 0;
        }
    }

}