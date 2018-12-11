#include "MP_MQ2.h"
const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_MQ2::ERRORS = errors_p;

MP_MQ2::MP_MQ2(uint8_t pin)
	:pin(pin)
{
}

int MP_MQ2::init()
{
	pinMode(this->pin, INPUT);
	return 0;
}

void MP_MQ2::printStatus()
{
    Serial.print(F("percent = "));
	Serial.println(percent);
}

void MP_MQ2::update(unsigned long time)
{
    percent = (analogRead(pin)/1023.0)*100;
}

double MP_MQ2::getPercent()
{
	return percent;
}
