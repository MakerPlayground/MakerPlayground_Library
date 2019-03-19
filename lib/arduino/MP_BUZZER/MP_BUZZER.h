#ifndef MP_BUZZER_H
#define MP_BUZZER_H

#include "MP_DEVICE.h"

class MP_BUZZER
{
public:
	MP_BUZZER(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void beep();
	void play(double frequency, double duration);

private:
	uint8_t pin;
	boolean playing;
	unsigned long endTime;
};

#endif
