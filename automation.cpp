#include "automation.h"

#include "data.h"

#include "pump_controller.h"
#include "fan_controller.h"
#include "light_controller.h"

void runAutomation()
{
    if(systemStatus.mode != SystemMode::AUTOMATIC)
        return;

    updatePumpController();

    updateFanController();

    updateLightController();
}