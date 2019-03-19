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

	void on(char dir[], int speed);
	void off();
	//void reverse();                   //not implemented
	//void set_speed(uint8_t speed);    //not implemented

private:
	uint8_t inA;
	uint8_t inB;
	String status;
};

#endif
