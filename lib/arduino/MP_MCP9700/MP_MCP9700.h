#ifndef MP_MCP9700_H
#define MP_MCP9700_H

#include "MP_DEVICE.h"

class MP_MCP9700
{
public:
	MP_MCP9700(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	double getTemperature();

private:
	uint8_t pin;
	double value;
};

#endif
