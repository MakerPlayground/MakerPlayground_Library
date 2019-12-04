#ifndef MP_HX711_H
#define MP_HX711_H

#include "MP_DEVICE.h"
#include "HX711.h"

class MP_HX711
{
public:

	MP_HX711(uint8_t dt_pin, uint8_t sck_pin, float scale_factor);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void setZero();
	void setScale(float scale_factor);

    double getWeight();

private:
	uint8_t dt_pin;
	uint8_t sck_pin;
    float scale_factor;
    double weight = 0.0;
    HX711 scale;
};
#endif
