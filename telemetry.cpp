#include "telemetry.h"

#include "data.h"
#include "logger.h"
#include "config.h"
#include "mav_wifi.h"

#include <HTTPClient.h>
#include <WiFi.h>

Telemetry getTelemetry()
{
    Telemetry t;

    t.timestamp = time(nullptr);

    t.temperature = sensors.temperature;
    t.pressure = sensors.pressure;

    t.soilRaw = sensors.soilRaw;
    t.soilPercent = sensors.soilPercent;

    t.fan = actuators.fan;
    t.pump = actuators.pump;
    t.growLight = actuators.growLight;

    return t;
}

void initTelemetry()
{
    Logger::info("Telemetria inicializada");
}

void printTelemetry()
{
    Telemetry t = getTelemetry();

    Serial.println();
    Serial.println("========== TELEMETRIA ==========");

    struct tm timeInfo;

    localtime_r(&t.timestamp, &timeInfo);

    Serial.print("Timestamp: ");

    Serial.printf(
        "%02d/%02d/%04d %02d:%02d:%02d\n",
        timeInfo.tm_mday,
        timeInfo.tm_mon + 1,
        timeInfo.tm_year + 1900,
        timeInfo.tm_hour,
        timeInfo.tm_min,
        timeInfo.tm_sec
    );

    Serial.print("Temperatura: ");
    Serial.print(t.temperature);
    Serial.println(" C");

    Serial.print("Presion: ");
    Serial.print(t.pressure);
    Serial.println(" hPa");

    Serial.print("Suelo RAW: ");
    Serial.println(t.soilRaw);

    Serial.print("Suelo: ");
    Serial.print(t.soilPercent);
    Serial.println(" %");

    Serial.print("Ventilador: ");
    Serial.println(t.fan ? "ON" : "OFF");

    Serial.print("Bomba: ");
    Serial.println(t.pump ? "ON" : "OFF");

    Serial.print("Grow Light: ");
    Serial.println(t.growLight ? "ON" : "OFF");

    Serial.println("================================");
}

bool sendTelemetry()
{
    if (!isWiFiConnected())
    {
        Logger::warning("No se puede enviar telemetria: WiFi desconectado");
        return false;
    }

    Telemetry t = getTelemetry();

    HTTPClient http;

    String url =
        String("http://") +
        API_HOST +
        ":" +
        String(API_PORT) +
        API_TELEMETRY_PATH;

    http.begin(url);

    http.addHeader("Content-Type", "application/json");

    String json = "{";

    json += "\"timestamp\":\"";

    struct tm timeInfo;
    gmtime_r(&t.timestamp, &timeInfo);

    char timestamp[25];

    strftime(
        timestamp,
        sizeof(timestamp),
        "%Y-%m-%dT%H:%M:%SZ",
        &timeInfo
    );

    json += timestamp;
    json += "\",";

    json += "\"temperature\":";
    json += String(t.temperature, 2);
    json += ",";

    json += "\"pressure\":";
    json += String(t.pressure, 2);
    json += ",";

    json += "\"soilRaw\":";
    json += String(t.soilRaw);
    json += ",";

    json += "\"soilPercent\":";
    json += String(t.soilPercent, 2);
    json += ",";

    json += "\"fan\":";
    json += t.fan ? "true" : "false";
    json += ",";

    json += "\"pump\":";
    json += t.pump ? "true" : "false";
    json += ",";

    json += "\"growLight\":";
    json += t.growLight ? "true" : "false";

    json += "}";

    Logger::info("Enviando telemetria...");

    Serial.println(json);

    int httpCode = http.POST(json);

    if (httpCode > 0)
    {
        Serial.print("HTTP: ");
        Serial.println(httpCode);

        String response = http.getString();

        Serial.print("Respuesta: ");
        Serial.println(response);

        http.end();

        return httpCode >= 200 && httpCode < 300;
    }

    Logger::error("Error enviando telemetria");

    Serial.print("HTTP error: ");
    Serial.println(http.errorToString(httpCode));

    http.end();

    return false;
}