#include "VD_DIGITAL_OUT.h"

VD_DIGITAL_OUT::VD_DIGITAL_OUT(uint8_t txPin):
    txPin(txPin)
{
}

int VD_DIGITAL_OUT::init() 
{
    pinMode(txPin, OUTPUT);

    isTxHigh = false;
    digitalWrite(txPin, LOW);

    return ERR_OK;
}

void VD_DIGITAL_OUT::update(unsigned long current_time) 
{
    
}

void VD_DIGITAL_OUT::printStatus()
{
    Serial.print(F("output value is now "));
    Serial.println(isTxHigh);
}

void VD_DIGITAL_OUT::writeHigh() {
    isTxHigh = true;
    digitalWrite(txPin, HIGH);
}

void VD_DIGITAL_OUT::writeLow() {
    isTxHigh = false;
    digitalWrite(txPin, LOW);
}