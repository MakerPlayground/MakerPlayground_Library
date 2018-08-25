#include "MP_DHT11.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_DHT11::ERRORS = errors_p;

MP_DHT11::MP_DHT11(int pin, const String &tag)
	:sensor(DHT(pin,11))
	,pin(pin)
{
}

int MP_DHT11::init()
{
	this->humidity = 0;
	this->temperature = 25;
	sensor.begin();
	return 0;
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
