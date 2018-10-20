#ifndef MP_NTC_NCP_WF_H
#define MP_NTC_NCP_WF_H

#include "MP_DEVICE.h"
#include <math.h>

class MP_NTC_NCP_WF
{
public:
	MP_NTC_NCP_WF(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getTemperature();

private:
	uint8_t pin;
	const int B = 4255;   // B value of the thermistor
	double celcius;
};

#endif
