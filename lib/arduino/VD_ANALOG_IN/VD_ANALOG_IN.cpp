#include "VD_ANALOG_IN.h"

VD_ANALOG_IN::VD_ANALOG_IN(uint8_t rxPin):
    rxPin(rxPin)
{
}

int VD_ANALOG_IN::init() 
{
    pinMode(rxPin, INPUT);
    return ERR_OK;
}

void VD_ANALOG_IN::update(unsigned long current_time) 
{
    percent = analogRead(rxPin);
}

void VD_ANALOG_IN::printStatus()
{
    Serial.print(F("value read = "));
    Serial.println(percent);
}

double VD_ANALOG_IN::getPercent() {
    return percent;
}