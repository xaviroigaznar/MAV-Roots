#include "logger.h"
#include "config.h"
#include "oled.h"
#include "boot.h"
#include "sensors.h"
#include "data.h"
#include "actuators.h"
#include "automation.h"
#include "mav_wifi.h"
#include "clock.h"
#include "telemetry.h"

#include <Wire.h>

/* void setup()
{
    Serial.begin(115200);
    delay(2000);

    Wire.begin(8, 9);

    Serial.println();
    Serial.println("Escaneando bus I2C...");

    byte encontrados = 0;

    for (uint8_t address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        byte error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("Encontrado dispositivo en 0x");

            if (address < 16)
                Serial.print("0");

            Serial.println(address, HEX);

            encontrados++;
        }
        else if (error != 2)
        {
            Serial.print("Direccion 0x");

            if (address < 16)
                Serial.print("0");

            Serial.print(address, HEX);

            Serial.print(" -> Error ");

            Serial.println(error);
        }
    }

    if (encontrados == 0)
        Serial.println("No se encontraron dispositivos.");

    Serial.println("Escaneo finalizado.");
} */

void setup()
{
    Logger::begin();

    Wire.begin(I2C_SDA, I2C_SCL);

    initOLED();

    initActuators();

    bootBegin();

    bootUpdate("Logger", BootStatus::OK);

    bootUpdate("I2C", BootStatus::OK);

    if(initBMP280())
        bootUpdate("BMP280", BootStatus::OK);
    else
        bootUpdate("BMP280", BootStatus::ERROR);

    if(initADS1115())
        bootUpdate("ADS1115", BootStatus::OK);
    else
        bootUpdate("ADS1115", BootStatus::ERROR);

    if (initWiFi())
    {
        Logger::info("WiFi OK");
    }
    else
    {
        Logger::error("WiFi ERROR");
    }

    if (isWiFiConnected())
    {
        if (initClock())
        {
            Logger::info("Clock OK");
        }
        else
        {
            Logger::error("Clock ERROR");
        }
        bootUpdate("WiFi", BootStatus::OK);
    }
    else
    {
        bootUpdate("WiFi", BootStatus::ERROR);
    }

    initTelemetry();

    bootFinish();
}

void loop()
{
    readBMP280();

    readSoilMoisture();

    runAutomation();

    updateOLED();

    static unsigned long lastTelemetry = 0;

    if (millis() - lastTelemetry >= TELEMETRY_INTERVAL)
    {
        lastTelemetry = millis();

        printTelemetry();
        sendTelemetry();
    }

    delay(1000);
}