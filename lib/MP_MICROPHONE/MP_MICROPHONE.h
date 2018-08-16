#ifndef MP_MICROPHONE_H
#define MP_MICROPHONE_H

#include <Arduino.h>
#define MP_MICROPHONE_MAX_ARRAY 20

class MP_MICROPHONE
{
public:
	MP_MICROPHONE(uint8_t pin, const String &tag);

	void init()
	double getSoundLevel();

private:
	uint8_t pin;
	double normal;
	const String tag;
};

#endif
