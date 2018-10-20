#ifndef VD_DIGITAL_OUT_H
#define VD_DIGITAL_OUT_H

#include "MP_DEVICE.h"

class VD_DIGITAL_OUT
{
public:
	VD_DIGITAL_OUT(uint8_t txPin);
	int init();
	void update(unsigned long time);
	void printStatus();
	static const char* const* ERRORS;

	void writeHigh();
	void writeLow();

private:
	uint8_t txPin;
    bool isTxHigh;
};

#endif
