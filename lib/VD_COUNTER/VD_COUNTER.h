#ifndef VD_COUNTER_H
#define VD_COUNTER_H

#include <Arduino.h>

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
	bool checkValue(int value);

private:
	int value;
};

#endif
