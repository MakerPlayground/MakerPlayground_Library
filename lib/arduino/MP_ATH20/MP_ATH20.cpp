#include "MP_ATH20.h"

#define UPDATE_INTERVAL 50

MP_ATH20::MP_ATH20()
{
}

int MP_ATH20::init()
{
    this->humidity = 0;
    this->celsius = 0;
    this->isValid = true;
    ATH.begin();
    return MP_ERR_OK;
}

void MP_ATH20::update(unsigned long current_time)
{
    float humidity, temp;
    int ret = ATH.getSensor(&humidity, &temp);
    if (ret) {
        this->isValid = false;
    } else {
        this->isValid = true;
        this->humidity = humidity * 100.0;
        this->celsius = temp;
    }
}

void MP_ATH20::printStatus()
{
    if (isValid) {
        Serial.print(F("humidity = "));
        Serial.print(this->humidity);

        Serial.print(F(" , temperature (C) = "));
        Serial.println(this->celsius);
    } else {
        Serial.print(F("Can't get sensor data"));
    }
}

double MP_ATH20::getTemperature()
{
    return this->celsius;
}

double MP_ATH20::getHumidity()
{
    return this->humidity;
}
