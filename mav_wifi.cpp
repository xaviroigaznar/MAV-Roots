#include "mav_wifi.h"

#include "config.h"
#include "logger.h"

#include <WiFi.h>

bool initWiFi()
{
    Logger::info("Inicializando WiFi...");

    WiFi.mode(WIFI_MODE_STA);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    const unsigned long timeout = 15000;
    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED &&
           millis() - start < timeout)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();

    if (WiFi.status() != WL_CONNECTED)
    {
        Logger::error("No se pudo conectar al WiFi");

        return false;
    }

    Logger::info("WiFi conectado");

    Serial.print("IP: ");
    Serial.println(WiFi.localIP());

    return true;
}

bool isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}