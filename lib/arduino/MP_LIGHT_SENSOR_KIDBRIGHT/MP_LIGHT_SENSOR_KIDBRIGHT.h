#ifndef MP_LIGHT_SENSOR_KIDBRIGHT_H
#define MP_LIGHT_SENSOR_KIDBRIGHT_H

#include "MP_DEVICE.h"

class MP_LIGHT_SENSOR_KIDBRIGHT
{
public:
	MP_LIGHT_SENSOR_KIDBRIGHT(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getPercent();

private:
	uint8_t pin;
	double value;
};

#endif
