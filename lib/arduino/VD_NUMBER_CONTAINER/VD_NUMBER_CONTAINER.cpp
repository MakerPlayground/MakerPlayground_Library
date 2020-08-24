#include "VD_NUMBER_CONTAINER.h"

VD_NUMBER_CONTAINER::VD_NUMBER_CONTAINER()
{
}

int VD_NUMBER_CONTAINER::init() 
{
    return MP_ERR_OK;
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

bool VD_NUMBER_CONTAINER::checkValue(double value)
{
    return this->value == value;
}