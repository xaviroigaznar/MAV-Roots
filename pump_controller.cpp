#include "pump_controller.h"

#include "config.h"
#include "data.h"
#include "actuators.h"

void updatePumpController()
{
    if(sensors.soilPercent < SOIL_MIN)
    {
        pumpOn();
    }
    else
    {
        pumpOff();
    }
}