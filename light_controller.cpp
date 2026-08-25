#include "light_controller.h"

#include "clock.h"
#include "actuators.h"
#include "config.h"
#include "data.h"

void updateLightController()
{
    if (!isClockValid())
        return;

    int hour = getCurrentHour();

    if (hour >= 14 || hour < 8)
    {
        lightOn();
    }
    else
    {
        lightOff();
    }
}