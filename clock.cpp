#include "clock.h"

#include "logger.h"

#include <time.h>

#define NTP_SERVER_1 "pool.ntp.org"
#define NTP_SERVER_2 "time.nist.gov"

#define TIMEZONE "CET-1CEST,M3.5.0,M10.5.0/3"

bool initClock()
{
    Logger::info("Inicializando reloj...");

    configTzTime(
        TIMEZONE,
        NTP_SERVER_1,
        NTP_SERVER_2);

    struct tm timeInfo;

    if (!getLocalTime(&timeInfo, 10000))
    {
        Logger::error("No se pudo sincronizar el reloj");

        return false;
    }

    Logger::info("Reloj sincronizado");

    Serial.printf(
        "Fecha: %02d/%02d/%04d\n",
        timeInfo.tm_mday,
        timeInfo.tm_mon + 1,
        timeInfo.tm_year + 1900);

    Serial.printf(
        "Hora: %02d:%02d:%02d\n",
        timeInfo.tm_hour,
        timeInfo.tm_min,
        timeInfo.tm_sec);

    return true;
}

bool isClockValid()
{
    time_t now;

    time(&now);

    // Consideramos válida una fecha posterior a 2024
    return now > 1704067200;
}

int getCurrentHour()
{
    struct tm timeInfo;

    if (!getLocalTime(&timeInfo))
        return -1;

    Serial.println("Current hour");
    Serial.print(timeInfo.tm_hour);
    return timeInfo.tm_hour;
}

int getCurrentMinute()
{
    struct tm timeInfo;

    if (!getLocalTime(&timeInfo))
        return -1;

    return timeInfo.tm_min;
}

int getCurrentSecond()
{
    struct tm timeInfo;

    if (!getLocalTime(&timeInfo))
        return -1;

    return timeInfo.tm_sec;
}