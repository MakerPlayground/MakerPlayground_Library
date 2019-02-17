#include "MP_DHT12.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Can't connect to DHT12";
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_DHT12::ERRORS = errors_p;

#define UPDATE_INTERVAL 50

MP_DHT12::MP_DHT12()
	:sensor(dht12(0x5c))
{
}

int MP_DHT12::init()
{
	dht::ReadStatus chk = sensor.read();
	if(chk != dht::OK)
	{
		return 1;
	}
	return 0;
}

void MP_DHT12::update(unsigned long current_time)
{
	if (current_time - last_update > UPDATE_INTERVAL) {
		dht::ReadStatus chk = sensor.read();
		if(chk  == dht::OK)
		{
			temperature = (double) sensor.getTemperature() / 10.0;
			humidity = (double) sensor.getHumidity() / 10.0;
		}
		last_update = current_time;
	}
}

void MP_DHT12::printStatus()
{
	Serial.print(F("Temperature = "));
	Serial.println(temperature);

	Serial.print(F("Humidity = "));
	Serial.println(humidity);
}

double MP_DHT12::getTemperature()
{
	return temperature;
}

double MP_DHT12::getHumidity()
{
	return humidity;
}
