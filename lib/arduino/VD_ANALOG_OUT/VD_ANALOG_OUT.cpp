#include "VD_ANALOG_OUT.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* VD_ANALOG_OUT::ERRORS = errors_p;

VD_ANALOG_OUT::VD_ANALOG_OUT(uint8_t txPin):
    txPin(txPin)
{
}

int VD_ANALOG_OUT::init() 
{
    pinMode(txPin, OUTPUT);
    return 0;
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