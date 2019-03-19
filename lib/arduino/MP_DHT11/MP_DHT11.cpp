#include "MP_DHT11.h"

MP_DHT11::MP_DHT11(uint8_t pin)
	:sensor(DHT(pin,11))
	,pin(pin)
{
}

int MP_DHT11::init()
{
	this->humidity = 0;
	this->celcius = 0;
	sensor.begin();
	return ERR_OK;
}

void MP_DHT11::update(unsigned long current_time)
{
	this->humidity = sensor.readHumidity();
	this->celcius = sensor.readTemperature();
}

void MP_DHT11::printStatus()
{
	Serial.print(F("humidity = "));
	Serial.println(this->humidity);

	Serial.print(F("temperature (C) = "));
	Serial.println(this->celcius);
}

double MP_DHT11::getHumidity()
{
	return this->humidity;
}

double MP_DHT11::getTemperature()
{
	return this->celcius;
}
