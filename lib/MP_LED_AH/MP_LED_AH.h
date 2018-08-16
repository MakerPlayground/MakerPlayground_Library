#ifndef MP_LED_AH_H
#define MP_LED_AH_H

#include <Arduino.h>
class MP_LED_AH
{
public:
	MP_LED_AH(uint8_t pin, const String &tag);

	void init();
	void on(int brightness);
	void off();

private:
	uint8_t pin;
	const String tag;
};

#endif
