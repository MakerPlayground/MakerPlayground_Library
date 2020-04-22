#ifndef MP_L9110_H
#define MP_L9110_H

#include "MP_DEVICE.h"

class MP_L9110
{
public:
	MP_L9110(uint8_t inA, uint8_t inB);

	int init();
	void update(unsigned long current_time);
	void printStatus();

	void on(uint8_t dir, int speed);
	void off();   //not implemented

private:
	uint8_t inA;
	uint8_t inB;
	String status;
};

#endif
