#include "MP_DHT22.h"

#define UPDATE_INTERVAL 50

MP_DHT22::MP_DHT22(uint8_t pin)
	:sensor(DHT(pin, 22))
	,pin(pin)
{
}

int MP_DHT22::init()
{
	this->humidity = 0;
	this->celcius = 0;
	sensor.begin();
	return ERR_OK;
}

void MP_DHT22::update(unsigned long current_time)
{
	this->humidity = sensor.readHumidity();
	this->celcius = sensor.readTemperature();
}

void MP_DHT22::printStatus()
{
	Serial.print(F("humidity = "));
	Serial.print(this->humidity);

	Serial.print(F(" , temperature (C) = "));
	Serial.println(this->celcius);
}

double MP_DHT22::getTemperature()
{
	return this->celcius;
}

double MP_DHT22::getHumidity()
{
	return this->humidity;
}
