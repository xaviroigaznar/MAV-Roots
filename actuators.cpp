#include "actuators.h"
#include "config.h"
#include "data.h"

void initActuators()
{
    pinMode(PIN_PUMP, OUTPUT);
    pinMode(PIN_FAN, OUTPUT);
    pinMode(PIN_GROW_LIGHT, OUTPUT);

    allOff();
}

//======================================================
// BOMBA
//======================================================

void pumpOn()
{
    digitalWrite(PIN_PUMP, ACTUATOR_ON);
    actuators.pump = true;
}

void pumpOff()
{
    digitalWrite(PIN_PUMP, ACTUATOR_OFF);
    actuators.pump = false;
}

void togglePump()
{
    if(actuators.pump)
        pumpOff();
    else
        pumpOn();
}

//======================================================
// VENTILADOR
//======================================================

void fanOn()
{
    digitalWrite(PIN_FAN, ACTUATOR_ON);
    actuators.fan = true;
}

void fanOff()
{
    digitalWrite(PIN_FAN, ACTUATOR_OFF);
    actuators.fan = false;
}

void toggleFan()
{
    if(actuators.fan)
        fanOff();
    else
        fanOn();
}

//======================================================
// LUZ
//======================================================

void lightOn()
{
    digitalWrite(PIN_GROW_LIGHT, ACTUATOR_ON);
    actuators.growLight = true;
}

void lightOff()
{
    digitalWrite(PIN_GROW_LIGHT, ACTUATOR_OFF);
    actuators.growLight = false;
}

void toggleLight()
{
    if(actuators.growLight)
        lightOff();
    else
        lightOn();
}

//======================================================
// ESTADO
//======================================================

bool isPumpOn()
{
    return actuators.pump;
}

bool isFanOn()
{
    return actuators.fan;
}

bool isLightOn()
{
    return actuators.growLight;
}

//======================================================
// APAGAR TODO
//======================================================

void allOff()
{
    digitalWrite(PIN_PUMP, ACTUATOR_OFF);
    digitalWrite(PIN_FAN, ACTUATOR_OFF);
    digitalWrite(PIN_GROW_LIGHT, ACTUATOR_OFF);

    actuators.pump = false;
    actuators.fan = false;
    actuators.growLight = false;
}