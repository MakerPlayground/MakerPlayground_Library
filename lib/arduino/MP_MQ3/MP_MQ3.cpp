#include "MP_MQ3.h"
const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_MQ3::ERRORS = errors_p;

MP_MQ3::MP_MQ3(uint8_t pin)
	:pin(pin)
{
}

int MP_MQ3::init()
{
	pinMode(this->pin, INPUT);
	return 0;
}

void MP_MQ3::printStatus()
{
    Serial.print(F("percent = "));
	Serial.println(percent);
}

void MP_MQ3::update(unsigned long time)
{
    percent = (analogRead(pin)/1023.0)*100;
}

double MP_MQ3::getPercent()
{
	return percent;
}
