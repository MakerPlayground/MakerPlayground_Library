#ifndef MP_PIR_H
#define MP_PIR_H

#include "MP_DEVICE.h"

class MP_PIR
{
public:
	MP_PIR(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool isDetected();
	bool isNotDetected();

private:
	uint8_t pin;
	bool isMotionDetected;
};
#endif
