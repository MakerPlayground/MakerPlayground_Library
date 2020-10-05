#include "MP_MQ2.h"

MP_MQ2::MP_MQ2(uint8_t pin)
	:pin(pin)
{
}

int MP_MQ2::init()
{
	pinMode(this->pin, INPUT);
	return MP_ERR_OK;
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
