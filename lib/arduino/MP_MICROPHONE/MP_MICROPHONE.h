#ifndef MP_MICROPHONE_H
#define MP_MICROPHONE_H

#include "MP_DEVICE.h"

class MP_MICROPHONE
{
public:
	MP_MICROPHONE(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getSoundLevel();

private:
	uint8_t pin;
	double soundLevel;
	unsigned long startMillis = 0;
	int signalMin = 1024;
	int signalMax = 0;
};

#endif
