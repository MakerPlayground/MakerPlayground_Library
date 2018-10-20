#ifndef VD_ANALOG_IN_H
#define VD_ANALOG_IN_H

#include "MP_DEVICE.h"

class VD_ANALOG_IN
{
public:
	VD_ANALOG_IN(uint8_t rxPin);
	int init();
	void update(unsigned long time);
	void printStatus();
	static const char* const* ERRORS;

	double getPercent();

private:
	uint8_t rxPin;
    double percent;
};

#endif
