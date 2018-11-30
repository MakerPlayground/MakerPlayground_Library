#ifndef VD_COUNTER_H
#define VD_COUNTER_H

#include "MP_DEVICE.h"

class VD_COUNTER
{
public:
	VD_COUNTER();
	int init();
	void update(unsigned long time);
	void printStatus();
	static const char* const* ERRORS;

	void setValue(int value);
	int getValue();
	void increaseValue();
	void decreaseValue();
	void increaseValueBy(int change);
	bool checkValueEqual(int value);
	bool checkValueNotEqual(int value);

private:
	int value;
};

#endif
