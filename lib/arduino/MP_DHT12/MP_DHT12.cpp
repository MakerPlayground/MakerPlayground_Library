#include "MP_DHT12.h"

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
		return MP_ERR_CONNECT_DEVICE;
	}
	return MP_ERR_OK;
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
