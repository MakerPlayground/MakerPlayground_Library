#ifndef MP_PAJ7620U2_H
#define MP_PAJ7620U2_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "paj7620.h"

class MP_PAJ7620U2
{
public:
	MP_PAJ7620U2();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool isSwipeUp();
	bool isSwipeDown();
	bool isSwipeLeft();
	bool isSwipeRight();
	bool isMoveForward();
	bool isMoveBackward();
	bool isSpinClockwise();
	bool isSpinCounterClockwise();
	bool isWave();
	bool isNotDetected();

private:
	uint8_t state;
	uint8_t data;
	uint16_t result;
	unsigned long end_time;
	unsigned long next_reading = 0;
};

#endif
