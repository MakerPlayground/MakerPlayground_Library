#include "VD_NUMBER_CONTAINER.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* VD_NUMBER_CONTAINER::ERRORS = errors_p;

VD_NUMBER_CONTAINER::VD_NUMBER_CONTAINER()
{
}

int VD_NUMBER_CONTAINER::init() 
{
    return 0;
}

void VD_NUMBER_CONTAINER::update(unsigned long current_time) 
{

}

void VD_NUMBER_CONTAINER::printStatus()
{
    Serial.print(F("value = "));
    Serial.println(this->value);
}

void VD_NUMBER_CONTAINER::setValue(double value)
{
    this->value = value;
}

double VD_NUMBER_CONTAINER::getValue()
{
    return this->value;
}