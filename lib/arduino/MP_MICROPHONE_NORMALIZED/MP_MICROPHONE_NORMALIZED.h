#ifndef MP_MICROPHONE_NORMALIZED_H
#define MP_MICROPHONE_NORMALIZED_H

#include "MP_DEVICE.h"

#define NORMALIZE_FRAME_COUNT 20

class MP_MICROPHONE_NORMALIZED
{
public:
	MP_MICROPHONE_NORMALIZED(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	double getSoundLevel();

private:
	uint8_t pin;
	double normal;
	double soundLevel = 0.0;
};

#endif
