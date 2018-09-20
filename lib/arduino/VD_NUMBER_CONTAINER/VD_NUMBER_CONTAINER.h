#ifndef VD_NUMBER_CONTAINER_H
#define VD_NUMBER_CONTAINER_H

#include <Arduino.h>

class VD_NUMBER_CONTAINER
{
public:
	VD_NUMBER_CONTAINER();
	int init();
	void update(unsigned long time);
	void printStatus();
	static const char* const* ERRORS;

	void setValue(double value);
	double getValue();
	bool checkValue(double value);

private:
	double value;
};

#endif
