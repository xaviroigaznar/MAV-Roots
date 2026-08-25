#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Arduino.h>

struct Telemetry
{
    time_t timestamp;

    float temperature;
    float pressure;

    int soilRaw;
    float soilPercent;

    bool fan;
    bool pump;
    bool growLight;
};

void initTelemetry();

Telemetry getTelemetry();

void printTelemetry();

bool sendTelemetry();

#endif