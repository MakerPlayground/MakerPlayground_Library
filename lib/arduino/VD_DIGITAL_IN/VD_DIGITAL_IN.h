#ifndef VD_DIGITAL_IN_H
#define VD_DIGITAL_IN_H

#include "MP_DEVICE.h"

class VD_DIGITAL_IN
{
public:
	VD_DIGITAL_IN(uint8_t rxPin);
	int init();
	void update(unsigned long time);
	void printStatus();
	static const char* const* ERRORS;

	bool readLow();
	bool readHigh();

private:
	uint8_t rxPin;
    bool isRxHigh;
};

#endif
