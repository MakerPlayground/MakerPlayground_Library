#ifndef MP_PAM8302
#define MP_PAM8302

#include <Arduino.h>

class MP_PAM8302
{
public:
	MP_PAM8302(uint8_t speakerPin);

	void init();
	void beep(float percentage, uint16_t dur);
	void tone(uint16_t hz, uint16_t dur);

private:
	uint8_t speakerPin;
};

#endif
