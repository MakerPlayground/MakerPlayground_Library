#ifndef MP_RELAY_H
#define MP_RELAY_H

#include "MP_DEVICE.h"

class MP_RELAY
{
public:
	MP_RELAY(uint8_t pin);
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
