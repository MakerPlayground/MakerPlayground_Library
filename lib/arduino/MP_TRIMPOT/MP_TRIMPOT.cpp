#include "MP_TRIMPOT.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_TRIMPOT::ERRORS = errors_p;

MP_TRIMPOT::MP_TRIMPOT(uint8_t pin)
	:pin(pin)
{
}

int MP_TRIMPOT::init()
{
	pinMode(this->pin, INPUT);
	return 0;
}

void MP_TRIMPOT::update(unsigned long current_time) 
{
#ifdef ESP32
	this->value = ((analogRead(pin) >> 2)/1023.0)*100;
#else
	this->value = (analogRead(pin)/1023.0)*100;
#endif
}

void MP_TRIMPOT::printStatus() {
	Serial.print(F("value = "));
	Serial.println(this->value);
}

double MP_TRIMPOT::getPercent()
{
	return this->value;
}
