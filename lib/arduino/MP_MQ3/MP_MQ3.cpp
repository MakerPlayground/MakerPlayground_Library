#include "MP_MQ3.h"

MP_MQ3::MP_MQ3(uint8_t pin)
	:pin(pin)
{
}

int MP_MQ3::init()
{
	pinMode(this->pin, INPUT);
	return ERR_OK;
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
