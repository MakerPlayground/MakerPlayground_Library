#include "MP_BME280.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Could not find a valid BME280 sensor, check wiring!";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_BME280::ERRORS = errors_p;

MP_BME280::MP_BME280()
{

}

int MP_BME280::init()
{
	if (!bme.begin()) {
		return 1;
	}
	this->end_time = 0;
	this->update(0);
	return 0;
}

void MP_BME280::update(unsigned long current_time)
{
	if (current_time == 0 || current_time - end_time > 50)
	{
		this->pressure = bme.readPressure() / 100.0;
		this->altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
		this->humidity = bme.readHumidity();
		this->temperature = bme.readTemperature();
		end_time = current_time;
	}
}

void MP_BME280::printStatus()
{
	Serial.print(F("pressure = "));
	Serial.println(this->getPressure());

	Serial.print(F("altitude = "));
	Serial.println(this->getAltitude());

	Serial.print(F("humidity = "));
	Serial.println(this->getHumidity());

	Serial.print(F("temperature = "));
	Serial.println(this->getTemperature());
}

double MP_BME280::getPressure()
{
	return this->pressure;
}

double MP_BME280::getAltitude()
{
	return this->altitude;
}

double MP_BME280::getHumidity()
{
	return this->humidity;
}

double MP_BME280::getTemperature()
{
	return this->temperature;
}
