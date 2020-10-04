#ifndef MP_GROVE_LEDBUTTON_H
#define MP_GROVE_LEDBUTTON_H

#include "MP_DEVICE.h"

class MP_GROVE_LEDBUTTON
{
public:
	MP_GROVE_LEDBUTTON(uint8_t ledPin, uint8_t buttonPin);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	bool isPress();
	bool isPressAndRelease();
	bool isNotPress();

	void on(int brightness);
    void off();

private:
	uint8_t ledPin;
	uint8_t buttonPin;
	unsigned long checkpoint;
	enum ButtonState { NOTHING, PRESSED, JUST_RELEASE };
	ButtonState state = NOTHING;
};

#endif
