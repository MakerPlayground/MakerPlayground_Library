#include "MP_AHT20.h"

#define UPDATE_INTERVAL 50

MP_AHT20::MP_AHT20()
{
}

int MP_AHT20::init()
{
    this->temp = 0;
    this->humid = 0;
    this->isValid = true;
    if (!aht.begin())
    {
        return MP_ERR_CONNECT_DEVICE;
    }
    return MP_ERR_OK;
}

void MP_AHT20::update(unsigned long current_time)
{
    if (current_time - last_update > UPDATE_INTERVAL)
    {
        sensors_event_t h, t;
        if (aht.getEvent(&h, &t))
        {
            this->temp = t.temperature;
            this->humid = h.relative_humidity;
            this->isValid = true;
        } else {
            this->isValid = false;
        }
        last_update = current_time;
    }
}

void MP_AHT20::printStatus()
{
    if (isValid)
    {
        Serial.print(F("humidity (%RH) = "));
        Serial.print(this->humid);

        Serial.print(F(" , temperature (C) = "));
        Serial.println(this->temp);
    }
    else
    {
        Serial.print(F("Can't get sensor data"));
    }
}

double MP_AHT20::getTemperature()
{
    return this->temp;
}

double MP_AHT20::getHumidity()
{
    return this->humid;
}
