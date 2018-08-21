#ifndef MP_MICROPHONE_NORMALIZED_H
#define MP_MICROPHONE_NORMALIZED_H

#include <Arduino.h>
#define NORMALIZE_FRAME_COUNT 20

class MP_MICROPHONE_NORMALIZED
{
public:
	MP_MICROPHONE_NORMALIZED(uint8_t pin, const String &tag);

	void init()
	double getSoundLevel();

private:
	uint8_t pin;
	double normal;
	const String tag;
};

#endif
