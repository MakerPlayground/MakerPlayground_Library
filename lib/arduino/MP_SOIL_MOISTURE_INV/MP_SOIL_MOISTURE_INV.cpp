#include "MP_SOIL_MOISTURE_INV.h"

MP_SOIL_MOISTURE_INV::MP_SOIL_MOISTURE_INV(uint8_t pin)
	:pin(pin)
{
}

int MP_SOIL_MOISTURE_INV::init()
{
	pinMode(pin, INPUT);
	return MP_ERR_OK;
}

void MP_SOIL_MOISTURE_INV::update(unsigned long current_time)
{
	this->value = 100.0 - (analogRead(pin) / 1023.0) * 100.0;
}

void MP_SOIL_MOISTURE_INV::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double MP_SOIL_MOISTURE_INV::getPercent()
{
	return value;
}
