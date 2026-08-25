#include <Arduino.h>
#include "scheduler.h"

bool everySecond()
{
    static unsigned long last = 0;

    if(millis()-last >=1000)
    {
        last=millis();
        return true;
    }

    return false;
}