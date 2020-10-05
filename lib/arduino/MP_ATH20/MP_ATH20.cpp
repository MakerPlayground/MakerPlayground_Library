#include "MP_ATH20.h"

#define UPDATE_INTERVAL 50

MP_ATH20::MP_ATH20()
{
}

int MP_ATH20::init()
{
	this->humidity = 0;
	this->celcius = 0;
  this->isValid = true;
	ATH.begin();
	return MP_ERR_OK;
}

void MP_ATH20::update(unsigned long current_time)
{
  float humi, temp;
  int ret = ATH.getSensor(&humi, &temp);
  if (ret) {
    isValid = false;
  } else {
    isValid = true;
  }
	this->humidity = humi;
	this->celcius = temp;
}

void MP_ATH20::printStatus()
{
  if (isValid) {
    Serial.print(F("humidity = "));
    Serial.print(this->humidity);

    Serial.print(F(" , temperature (C) = "));
    Serial.println(this->celcius);
  } else {
    Serial.print(F("Can't get sensor data"));
  }
}

double MP_ATH20::getTemperature()
{
	return this->celcius;
}

double MP_ATH20::getHumidity()
{
	return this->humidity;
}
