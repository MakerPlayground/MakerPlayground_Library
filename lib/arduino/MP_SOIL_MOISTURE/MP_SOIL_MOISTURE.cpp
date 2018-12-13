#include "MP_SOIL_MOISTURE.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_SOIL_MOISTURE::ERRORS = errors_p;

MP_SOIL_MOISTURE::MP_SOIL_MOISTURE(uint8_t pin)
	:pin(pin)
{
}

int MP_SOIL_MOISTURE::init()
{
	pinMode(pin, INPUT);
	return 0;
}

void MP_SOIL_MOISTURE::update(unsigned long current_time)
{
	this->value = (analogRead(pin) / 1023.0) * 100.0;
}

void MP_SOIL_MOISTURE::printStatus()
{
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double MP_SOIL_MOISTURE::getPercent()
{
	return value;
}
