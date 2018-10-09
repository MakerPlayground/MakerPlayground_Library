#include "MP_BMP280.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Could not find a valid BMP280 sensor, check wiring!";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_BMP280::ERRORS = errors_p;

MP_BMP280::MP_BMP280()
{

}

int MP_BMP280::init()
{
	if (!bmp.begin()) {
		return 1;
	}
	this->end_time = 0;
	this->update(0);
	return 0;
}

void MP_BMP280::update(unsigned long current_time)
{
	if (current_time == 0 || current_time - end_time > 50)
	{
		this->pressure = bmp.readPressure() / 100.0;
		this->altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);
		this->temperature = bmp.readTemperature();
		end_time = current_time;
	}
}

void MP_BMP280::printStatus()
{
	Serial.print(F("pressure = "));
	Serial.println(this->getPressure());

	Serial.print(F("altitude = "));
	Serial.println(this->getAltitude());

	Serial.print(F("temperature = "));
	Serial.println(this->getTemperature());
}

double MP_BMP280::getPressure()
{
	return this->pressure;
}

double MP_BMP280::getAltitude()
{
	return this->altitude;
}

double MP_BMP280::getTemperature()
{
	return this->temperature;
}
