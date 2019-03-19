#include "VD_ANALOG_OUT.h"

VD_ANALOG_OUT::VD_ANALOG_OUT(uint8_t txPin):
    txPin(txPin)
{
}

int VD_ANALOG_OUT::init() 
{
    pinMode(txPin, OUTPUT);
    return ERR_OK;
}

void VD_ANALOG_OUT::update(unsigned long current_time) 
{
    
}

void VD_ANALOG_OUT::printStatus()
{
    Serial.print(F("value write =  "));
    Serial.println(_percent);
}

void VD_ANALOG_OUT::sendPercent(double percent) {
    _percent = percent;
    analogWrite(txPin, (int) (percent * 1024.0 / 100));
}