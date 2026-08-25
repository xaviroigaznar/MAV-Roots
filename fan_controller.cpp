#include "fan_controller.h"

#include "config.h"

#include "data.h"

#include "actuators.h"

void updateFanController()
{
    if(sensors.temperature > FAN_ON_TEMP)
    {
        fanOn();
    }

    if(sensors.temperature < FAN_OFF_TEMP)
    {
        fanOff();
    }
}