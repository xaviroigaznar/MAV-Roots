#ifndef DATA_H
#define DATA_H

#include <Arduino.h>

enum class SystemMode
{
    MANUAL,
    AUTOMATIC
};

struct SensorData
{
    float temperature = 0.0;
    float humidity = 0.0;
    float pressure = 0.0;

    float soilVoltage = 0.0;
    int16_t soilRaw = 0;
    float soilPercent = 0.0;

    bool bmpConnected = false;
    bool adsConnected = false;
};

struct ActuatorState
{
    bool pump = false;
    bool fan = false;
    bool growLight = false;
};

struct SystemStatus
{
    bool wifiConnected = false;
    bool oledConnected = false;

    unsigned long uptime = 0;

    SystemMode mode = SystemMode::AUTOMATIC;
};

extern SensorData sensors;
extern ActuatorState actuators;
extern SystemStatus systemStatus;

#endif