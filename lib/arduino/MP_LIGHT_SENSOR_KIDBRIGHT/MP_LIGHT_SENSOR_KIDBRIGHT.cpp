#include "MP_LIGHT_SENSOR_KIDBRIGHT.h"

MP_LIGHT_SENSOR_KIDBRIGHT::MP_LIGHT_SENSOR_KIDBRIGHT(uint8_t pin)
	:pin(pin)
{
}

int MP_LIGHT_SENSOR_KIDBRIGHT::init()
{
	pinMode(this->pin, INPUT);
  analogSetAttenuation(ADC_0db);	// acceptable range from 0-1v
	return MP_ERR_OK;
}

void MP_LIGHT_SENSOR_KIDBRIGHT::update(unsigned long current_time) 
{
	this->value = ((963 - analogRead(pin)) / 9.63);
	if (this->value < 0) {
		this->value = 0;
	}
}

double MP_LIGHT_SENSOR_KIDBRIGHT::getPercent()
{
	return this->value;
}

void MP_LIGHT_SENSOR_KIDBRIGHT::printStatus()
{
	Serial.print(F("Value = "));
	Serial.print(this->value);
}