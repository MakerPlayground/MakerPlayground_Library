#include "MP_PERCENT_REFLECTANCE.h"

MP_PERCENT_REFLECTANCE::MP_PERCENT_REFLECTANCE(uint8_t pin)
	:pin(pin)
{
}

int MP_PERCENT_REFLECTANCE::init()
{
	pinMode(pin, INPUT);
	return MP_ERR_OK;
}

void MP_PERCENT_REFLECTANCE::update(unsigned long current_time)
{
	this->value = (analogRead(pin) / 1023.0) * 100.0;
}

void MP_PERCENT_REFLECTANCE::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double MP_PERCENT_REFLECTANCE::getReflectance()
{
	return value;
}
