#include "logger.h"

void Logger::begin(uint32_t baudRate)
{
    Serial.begin(baudRate);

    delay(200);

    Serial.println();
    Serial.println("====================================");
    Serial.println("MAV-Roots");
    Serial.println("Logger inicializado");
    Serial.println("====================================");
}

void Logger::debug(const String& message)
{
    log(LogLevel::DEBUG, message);
}

void Logger::info(const String& message)
{
    log(LogLevel::INFO, message);
}

void Logger::warning(const String& message)
{
    log(LogLevel::WARNING, message);
}

void Logger::error(const String& message)
{
    log(LogLevel::ERROR, message);
}

void Logger::log(LogLevel level,
                 const String& message)
{
    Serial.print("[");
    Serial.print(getTimestamp());
    Serial.print("] ");

    Serial.print("[");
    Serial.print(levelToString(level));
    Serial.print("] ");

    Serial.println(message);
}

String Logger::getTimestamp()
{
    return String(millis());
}

String Logger::levelToString(LogLevel level)
{
    switch(level)
    {
        case LogLevel::DEBUG:
            return "DEBUG";

        case LogLevel::INFO:
            return "INFO";

        case LogLevel::WARNING:
            return "WARNING";

        case LogLevel::ERROR:
            return "ERROR";

        default:
            return "UNKNOWN";
    }
}