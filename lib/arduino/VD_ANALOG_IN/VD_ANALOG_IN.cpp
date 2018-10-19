#include "VD_ANALOG_IN.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* VD_ANALOG_IN::ERRORS = errors_p;

VD_ANALOG_IN::VD_ANALOG_IN(uint8_t rxPin):
    rxPin(rxPin)
{
}

int VD_ANALOG_IN::init() 
{
    pinMode(rxPin, INPUT);
    return 0;
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