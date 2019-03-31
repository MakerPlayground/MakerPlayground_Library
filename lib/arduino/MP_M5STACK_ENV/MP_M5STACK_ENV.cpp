#include "MP_M5STACK_ENV.h"

#define UPDATE_INTERVAL 50

MP_M5STACK_ENV::MP_M5STACK_ENV()
	:sensor(dht12(0x5c))
	, bmp(Adafruit_BMP280())
{
}

int MP_M5STACK_ENV::init()
{
	M5.begin();
	dht::ReadStatus chk = sensor.read();
	if(chk != dht::OK)
	{
		return ERR_CONNECT_DEVICE;
	}
	Wire.begin();
	if (!bmp.begin(0x76)) {
		return ERR_CONNECT_DEVICE;
	}
	return ERR_OK;
}

void MP_M5STACK_ENV::update(unsigned long current_time)
{
	if (current_time - last_update > UPDATE_INTERVAL) {
		dht::ReadStatus chk = sensor.read();
		if(chk  == dht::OK)
		{
			temperature = (double) sensor.getTemperature() / 10.0;
			humidity = (double) sensor.getHumidity() / 10.0;
		}
		
		pressure = bmp.readPressure() / 100.0;
		altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
		// this->humidity = bmp.readHumidity();
		// this->temperature = bmp.readTemperature();

		last_update = current_time;
	}
}

void MP_M5STACK_ENV::printStatus()
{
	Serial.print(F("pressure = "));
	Serial.println(getPressure());

	Serial.print(F("altitude = "));
	Serial.println(getAltitude());

	Serial.print(F("humidity = "));
	Serial.println(getHumidity());

	Serial.print(F("temperature = "));
	Serial.println(getTemperature());
}

double MP_M5STACK_ENV::getTemperature()
{
	return temperature;
}

double MP_M5STACK_ENV::getHumidity()
{
	return humidity;
}

double MP_M5STACK_ENV::getPressure()
{
	return pressure;
}

double MP_M5STACK_ENV::getAltitude()
{
	return altitude;
}