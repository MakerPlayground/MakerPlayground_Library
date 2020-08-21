#ifndef MP_LOAD_DRIVER_AL_H
#define MP_LOAD_DRIVER_AL_H

#include "MP_DEVICE.h"

class MP_LOAD_DRIVER_AL
{
public:
	MP_LOAD_DRIVER_AL(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	void on();
	void off();

private:
	uint8_t pin;
	bool isOn;
};

#endif
