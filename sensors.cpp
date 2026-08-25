#include "sensors.h"

#include "config.h"
#include "data.h"
#include "logger.h"

#include <Wire.h>

#include <Adafruit_BMP280.h>
#include <Adafruit_ADS1X15.h>

Adafruit_BMP280 bmp;
Adafruit_ADS1115 ads;

bool initBMP280()
{
    Logger::info("Inicializando BMP280...");

    if(!bmp.begin(BME280_ADDRESS))
    {
        Logger::error("BMP280 no encontrado");

        sensors.bmpConnected = false;

        return false;
    }

    uint8_t id = bmp.sensorID();

    Serial.print("Sensor ID: 0x");
    Serial.println(id, HEX);

    if(id != BMP280_CHIPID)
    {
        Logger::warning("El sensor no parece ser un BMP280");
    }

    bmp.setSampling(
        Adafruit_BMP280::MODE_NORMAL,
        Adafruit_BMP280::SAMPLING_X2,
        Adafruit_BMP280::SAMPLING_X16,
        Adafruit_BMP280::FILTER_X16,
        Adafruit_BMP280::STANDBY_MS_500);

    Logger::info("BMP280 detectado");

    sensors.bmpConnected = true;

    return true;
}

bool initADS1115()
{
    Logger::info("Inicializando ADS1115...");

    if(!ads.begin(0x48))
    {
        Logger::error("ADS1115 no encontrado");

        sensors.adsConnected = false;

        return false;
    }

    Logger::info("ADS1115 detectado");

    sensors.adsConnected = true;

    return true;
}

bool readBMP280()
{
    if(!sensors.bmpConnected)
        return false;

    sensors.temperature = bmp.readTemperature();

    // El BMP280 no mide humedad
    sensors.humidity = NAN;

    sensors.pressure =
        bmp.readPressure() / 100.0f;

    return true;
}

bool readSoilMoisture()
{
    if(!sensors.adsConnected)
        return false;

    int16_t value = ads.readADC_SingleEnded(0);

    sensors.soilRaw = value;

    float percent =
    (SOIL_RAW_DRY - value) * 100.0f /
    (SOIL_RAW_DRY - SOIL_RAW_WET);

    percent = constrain(percent, 0.0f, 100.0f);

    sensors.soilPercent = percent;

    return true;
}