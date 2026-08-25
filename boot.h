#ifndef BOOT_H
#define BOOT_H

#include <Arduino.h>

enum class BootStatus
{
    PENDING,
    OK,
    ERROR
};

void bootBegin();

void bootUpdate(const String& module,
                BootStatus status);

void bootFinish();

#endif