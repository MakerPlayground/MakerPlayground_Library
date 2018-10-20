#ifndef MP_LOAD_DRIVER_H
#define MP_LOAD_DRIVER_H

#include "MP_DEVICE.h"

class MP_LOAD_DRIVER
{
public:
	MP_LOAD_DRIVER(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;
	
	void on();
	void off();

private:
	uint8_t pin;
	bool isOn;
};

#endif
