#ifndef MP_IR_REFLECTOR_H
#define MP_IR_REFLECTOR_H

#include "MP_DEVICE.h"

class MP_IR_REFLECTOR
{
public:
	MP_IR_REFLECTOR(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool isDetected();
	bool isNotDetected();

private:
	uint8_t pin;
};
#endif
