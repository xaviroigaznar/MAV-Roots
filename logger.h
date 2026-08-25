#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class Logger
{
public:

    static void begin(uint32_t baudRate = 115200);

    static void debug(const String& message);

    static void info(const String& message);

    static void warning(const String& message);

    static void error(const String& message);

private:

    static void log(LogLevel level,
                    const String& message);

    static String getTimestamp();

    static String levelToString(LogLevel level);
};

#endif