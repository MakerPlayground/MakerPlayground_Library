#include "MP_LIGHT_SENSOR.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_LIGHT_SENSOR::ERRORS = errors_p;

MP_LIGHT_SENSOR::MP_LIGHT_SENSOR(uint8_t pin)
	:pin(pin)
{
}

int MP_LIGHT_SENSOR::init()
{
	pinMode(this->pin, INPUT);
	return 0;
}

void MP_LIGHT_SENSOR::update(unsigned long current_time) 
{
	this->value = (analogRead(pin)/1023.0)*100;
}

double MP_LIGHT_SENSOR::getPercent()
{
	return this->value;
}

void MP_LIGHT_SENSOR::printStatus()
{
	Serial.print(F("Value = "));
	Serial.print(this->value);
}