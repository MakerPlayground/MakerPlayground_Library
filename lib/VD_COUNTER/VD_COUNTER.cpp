#include "VD_COUNTER.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* VD_COUNTER::ERRORS = errors_p;

VD_COUNTER::VD_COUNTER()
{
}

int VD_COUNTER::init() 
{
    return 0;
}

void VD_COUNTER::update(unsigned long current_time) 
{

}

void VD_COUNTER::printStatus()
{
    Serial.print(F("value = "));
    Serial.println(this->value);
}

void VD_COUNTER::setValue(int value)
{
    this->value = value;
}

int VD_COUNTER::getValue()
{
    return this->value;
}

void VD_COUNTER::increaseValue()
{
    this->value = this->value + 1;
}

void VD_COUNTER::decreaseValue()
{
    this->value = this->value - 1;
}

void VD_COUNTER::increaseValueBy(int change)
{
    this->value = this->value + change;
}

bool VD_COUNTER::checkValue(int value)
{
    return this->value == value;
}