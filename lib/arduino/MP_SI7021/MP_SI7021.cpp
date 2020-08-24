#include "MP_SI7021.h"

MP_SI7021::MP_SI7021()
{

}

int MP_SI7021::init()
{
	sensor = Adafruit_Si7021();

	if (!sensor.begin()) {
		return MP_ERR_CONNECT_DEVICE;
	}

	this->end_time = 0;
	this->update(0);
	return MP_ERR_OK;
}

void MP_SI7021::update(unsigned long current_time)
{
	if (current_time == 0 || current_time - end_time > 50)
	{
		this->temperature = sensor.readTemperature();
		this->humidity = sensor.readHumidity();
		end_time = current_time;
	}
}

void MP_SI7021::printStatus()
{
	Serial.print(F("humidity = "));
	Serial.println(this->humidity);

	Serial.print(F("temperature = "));
	Serial.println(this->temperature);
}

double MP_SI7021::getTemperature()
{
	return this->temperature;
}

double MP_SI7021::getHumidity()
{
	return this->humidity;
}
