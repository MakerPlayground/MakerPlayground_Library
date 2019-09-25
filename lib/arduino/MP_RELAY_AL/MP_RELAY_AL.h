#ifndef MP_RELAY_AL_H
#define MP_RELAY_AL_H

#include "MP_DEVICE.h"

class MP_RELAY_AL
{
public:
	MP_RELAY_AL(uint8_t pin);
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
