#ifndef MP_LED_AL_H
#define MP_LED_AL_H

#include "MP_DEVICE.h"

class MP_LED_AL
{
public:
	MP_LED_AL(uint8_t pin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void on(int brightness);
	void off();
	
private:
	uint8_t pin;
	int brightness;
};

#endif
