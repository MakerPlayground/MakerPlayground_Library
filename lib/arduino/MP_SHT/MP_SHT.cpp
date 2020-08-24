#include "MP_SHT.h"

MP_SHT::MP_SHT()
{
}

int MP_SHT::init()
{
	Wire.begin();
	if (sht.init()) {
		return MP_ERR_OK;
	} else {
		return MP_ERR_CONNECT_DEVICE;
	}
}

void MP_SHT::update(unsigned long current_time) 
{
	sht.readSample();
}

void MP_SHT::printStatus() 
{
	Serial.print(F("Temp = "));
	Serial.println(sht.getTemperature());

	Serial.print(F("Humid = "));
	Serial.println(sht.getHumidity());
}

double MP_SHT::getTemperature()
{
	return sht.getTemperature();
}

double MP_SHT::getHumidity()
{
	return sht.getHumidity();
}
