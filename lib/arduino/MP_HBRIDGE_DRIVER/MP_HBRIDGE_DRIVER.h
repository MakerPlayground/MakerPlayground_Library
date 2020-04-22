#ifndef MP_HBRIDGE_DRIVER_H
#define MP_HBRIDGE_DRIVER_H

#include "MP_DEVICE.h"

class MP_HBRIDGE_DRIVER
{
public:
	MP_HBRIDGE_DRIVER(uint8_t inA, uint8_t inB);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void on(uint8_t dir, int speed);
	void off();

private:
	uint8_t inA;
	uint8_t inB;
};

#endif
