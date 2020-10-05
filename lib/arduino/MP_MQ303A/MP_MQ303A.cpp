#include "MP_MQ303A.h"

MP_MQ303A::MP_MQ303A(uint8_t pin_dat, uint8_t pin_sel)
	:pin_sel(pin_sel)
	,pin_dat(pin_dat)
{
}

int MP_MQ303A::init()
{
	pinMode(pin_sel, OUTPUT); // set the HEATER_SEL as digital output.
	pinMode(pin_dat, INPUT);
	digitalWrite(pin_sel, LOW);
	return MP_ERR_OK;
}

void MP_MQ303A::printStatus()
{
  Serial.print(F("percent = "));
	Serial.println(percent);
}

void MP_MQ303A::update(unsigned long time)
{
  percent = ((1023 - analogRead(pin_dat)) / 1023.0) * 100;
}

double MP_MQ303A::getPercent()
{
	return percent;
}
