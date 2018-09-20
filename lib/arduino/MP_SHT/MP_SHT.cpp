#include "MP_SHT.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Can't detect SHT Sensor. Please check connection!!!";
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_SHT::ERRORS = errors_p;

MP_SHT::MP_SHT()
{
}

int MP_SHT::init()
{
	Wire.begin();
	if (sht.init()) {
		return 0;
	} else {
		return 1;
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
