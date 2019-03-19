#ifndef MP_FLYINGFISH_FLAME_DETECTOR_H
#define MP_FLYINGFISH_FLAME_DETECTOR_H

#include "MP_DEVICE.h"

class MP_FLYINGFISH_FLAME_DETECTOR
{
public:
	MP_FLYINGFISH_FLAME_DETECTOR(uint8_t pin);

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getPercent();

private:
	uint8_t pin;
	int percent = 0;
	
};

#endif
