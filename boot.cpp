#include "boot.h"

#include "config.h"
#include "logger.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

struct BootItem
{
    String name;
    BootStatus status;
};

static BootItem items[] =
{
    {"Logger",      BootStatus::PENDING},
    {"I2C",         BootStatus::PENDING},
    {"OLED",        BootStatus::PENDING},
    {"BME280",      BootStatus::PENDING},
    {"ADS1115",     BootStatus::PENDING},
    {"Automation",  BootStatus::PENDING},
    {"WiFi",        BootStatus::PENDING}
};

static const uint8_t ITEM_COUNT =
sizeof(items) / sizeof(items[0]);


// Declaración adelantada
static void drawBootScreen();

void bootBegin()
{
    Logger::info("Boot iniciado");

    drawBootScreen();
}

void bootUpdate(const String& module,
                BootStatus status)
{
    for(uint8_t i=0;i<ITEM_COUNT;i++)
    {
        if(items[i].name == module)
        {
            items[i].status = status;

            break;
        }
    }

    drawBootScreen();

    switch(status)
    {
        case BootStatus::OK:
            Logger::info(module + " OK");
            break;

        case BootStatus::ERROR:
            Logger::error(module + " ERROR");
            break;

        default:
            break;
    }

    delay(250);
}

void bootFinish()
{
    Logger::info("Boot finalizado");

    delay(1000);
}

static void drawBootScreen()
{
    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(1);

    display.setCursor(0,0);

    display.println(PROJECT_NAME);
    display.println("Firmware " PROJECT_VERSION);
    display.println();

    for(uint8_t i=0;i<ITEM_COUNT;i++)
    {
        switch(items[i].status)
        {
            case BootStatus::PENDING:
                display.print("[ ] ");
                break;

            case BootStatus::OK:
                display.print("[OK] ");
                break;

            case BootStatus::ERROR:
                display.print("[ER] ");
                break;
        }

        display.println(items[i].name);
    }

    display.display();
}