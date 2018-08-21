#ifndef MP_MICROPHONE_H
#define MP_MICROPHONE_H

#include <Arduino.h>

class MP_MP_MICROPHONE
{
public:
	MP_MP_MICROPHONE(uint8_t pin,const String &tag);

	void init();
	double getSoundLevel();

private:
	uint8_t pin;
	const String tag;
};

#endif
