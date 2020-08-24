#include "MP_HX711.h"

MP_HX711::MP_HX711(uint8_t dt_pin, uint8_t sck_pin, float scale_factor)
	:dt_pin(dt_pin),
    sck_pin(sck_pin),
    scale_factor(scale_factor)
{
}

int MP_HX711::init()
{
	scale.begin(dt_pin, sck_pin);
    scale.set_scale(scale_factor);
    scale.tare();
    return MP_ERR_OK;
}

void MP_HX711::setZero()
{
	return scale.tare();
}

void MP_HX711::setScale(float scale_factor)
{
	return scale.set_scale(scale_factor);
}

double MP_HX711::getWeight()
{
    return weight;
}

void MP_HX711::update(unsigned long current_time)
{
    weight = scale.get_units(3);
}

void MP_HX711::printStatus()
{
    Serial.print(F("Weight is "));
    Serial.println(weight);
}
