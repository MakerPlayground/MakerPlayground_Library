#ifndef MP_HY_SRF05_H
#define MP_HY_SRF05_H

#include "MP_DEVICE.h"

class MP_HY_SRF05
{
public:
    MP_HY_SRF05(uint8_t echo ,uint8_t trig);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

    double getDistance();

private:
    uint8_t trig;
    uint8_t echo;
    double cm;
    unsigned long nextReading;
};

#endif