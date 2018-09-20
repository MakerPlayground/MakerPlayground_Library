#ifndef MP_MICROPHONE_NORMALIZED_H
#define MP_MICROPHONE_NORMALIZED_H

#include <Arduino.h>
#define NORMALIZE_FRAME_COUNT 20

class MP_MICROPHONE_NORMALIZED
{
public:
	MP_MICROPHONE_NORMALIZED(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;
	
	double getSoundLevel();

private:
	uint8_t pin;
	double normal;
};

#endif
