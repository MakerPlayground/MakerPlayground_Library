#include "MP_TRIMPOT.h"

MP_TRIMPOT::MP_TRIMPOT(uint8_t pin)
	:pin(pin)
{
}

int MP_TRIMPOT::init()
{
	pinMode(this->pin, INPUT);
	return MP_ERR_OK;
}

void MP_TRIMPOT::update(unsigned long current_time) 
{
	this->value = (analogRead(pin)/1023.0)*100;
}

void MP_TRIMPOT::printStatus() {
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double MP_TRIMPOT::getPercent()
{
	return this->value;
}
