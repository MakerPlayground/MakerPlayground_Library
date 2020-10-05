#ifndef MP_MQ303A_H
#define MP_MQ303A_H

#include "MP_DEVICE.h"

class MP_MQ303A
{
public:
	MP_MQ303A(uint8_t pin_dat, uint8_t pin_sel);

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getPercent();

private:
	uint8_t pin_sel;
	uint8_t pin_dat;
	double percent = 0;
};

#endif
