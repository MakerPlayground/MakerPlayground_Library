#ifndef MP_PAM8302_H
#define MP_PAM8302_H

#include <Arduino.h>

class MP_PAM8302
{
public:
	MP_PAM8302(uint8_t speakerPin);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void beep(float percentage, uint16_t dur);
	void tone(uint16_t hz, uint16_t dur);

private:
	uint8_t speakerPin;
};

#endif
