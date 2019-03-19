#ifndef VD_ANALOG_OUT_H
#define VD_ANALOG_OUT_H

#include "MP_DEVICE.h"

class VD_ANALOG_OUT
{
public:
	VD_ANALOG_OUT(uint8_t txPin);
	int init();
	void update(unsigned long time);
	void printStatus();

	void sendPercent(double percent);

private:
	uint8_t txPin;
    double _percent;
};

#endif
