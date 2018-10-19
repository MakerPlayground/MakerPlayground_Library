#include "VD_DIGITAL_IN.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* VD_DIGITAL_IN::ERRORS = errors_p;

VD_DIGITAL_IN::VD_DIGITAL_IN(uint8_t rxPin):
    rxPin(rxPin)
{
}

int VD_DIGITAL_IN::init() 
{
    pinMode(rxPin, INPUT);
    return 0;
}

void VD_DIGITAL_IN::update(unsigned long current_time) 
{
    isRxHigh = (digitalRead(rxPin) == HIGH);
}

void VD_DIGITAL_IN::printStatus()
{
    Serial.print(F("value read is now "));
    Serial.println(isRxHigh ? "high" : "low");
}

bool VD_DIGITAL_IN::readLow() {
    return !isRxHigh;
}

bool VD_DIGITAL_IN::readHigh() {
    return isRxHigh;
}