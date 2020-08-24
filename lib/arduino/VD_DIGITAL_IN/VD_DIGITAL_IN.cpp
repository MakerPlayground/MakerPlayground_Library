#include "VD_DIGITAL_IN.h"

VD_DIGITAL_IN::VD_DIGITAL_IN(uint8_t rxPin):
    rxPin(rxPin)
{
}

int VD_DIGITAL_IN::init() 
{
    pinMode(rxPin, INPUT);
    return MP_ERR_OK;
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