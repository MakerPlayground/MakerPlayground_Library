#include "MP_TMP007.h"

MP_TMP007::MP_TMP007()
{
}

int MP_TMP007::init()
{
	if (!tmp007.begin()) {
		return ERR_CONNECT_DEVICE;
	}
	this->end_time = 0;
	this->update(0);
	return ERR_OK;
}

void MP_TMP007::update(unsigned long current_time)
{
	if (current_time == 0 || current_time - end_time > 50) {
		this->celcius = tmp007.readObjTempC();
		end_time = current_time;
	}
}

void MP_TMP007::printStatus()
{
	Serial.print(F("Celcius = "));
	Serial.println(this->getTemperature());
}

double MP_TMP007::getTemperature()
{
	return this->celcius;
}