#include "oled.h"

#include "config.h"
#include "data.h"
#include "logger.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1);

bool initOLED()
{
    if(!display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS))
    {
        Logger::error("OLED no encontrada");
        systemStatus.oledConnected=false;
        return false;
    }

    systemStatus.oledConnected=true;

    Logger::info("OLED detectada");

    display.clearDisplay();

    display.display();

    return true;
}

void updateOLED()
{
    display.clearDisplay();

    display.setCursor(0,0);

    display.printf("T: %.1f C\n",
                   sensors.temperature);

    display.printf("H: %.1f %%\n",
                   sensors.humidity);

    display.printf("P: %.0f hPa\n",
                   sensors.pressure);

    display.printf("Soil: %d\n",
                   sensors.soilRaw);

    display.printf("S: %.0f %%\n",
                   sensors.soilPercent);

    display.println();

    display.print("P:");

    display.print(
        actuators.pump ?
        "ON":"OFF");

    display.print(" F:");

    display.print(
        actuators.fan ?
        "ON":"OFF");

    display.display();
}

void showSplash()
{
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(2);

    display.setCursor(0,0);

    display.println("MAV");

    display.setTextSize(1);

    display.println();

    display.println("Smart Garden");

    display.println();

    display.println("Firmware 0.1");

    display.display();

    delay(2000);
}