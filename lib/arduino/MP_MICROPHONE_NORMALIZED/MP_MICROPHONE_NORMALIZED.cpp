#include "MP_MICROPHONE_NORMALIZED.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_MICROPHONE_NORMALIZED::ERRORS = errors_p;

MP_MICROPHONE_NORMALIZED::MP_MICROPHONE_NORMALIZED(uint8_t pin)
	:pin(pin)
{
}

int MP_MICROPHONE_NORMALIZED::init()
{
	pinMode(this->pin, INPUT);
	normal = analogRead(pin);
	for(int i=1; i<NORMALIZE_FRAME_COUNT; i++)
	{
		normal = 0.8 * normal + 0.2 * (analogRead(pin) - normal);
	}
	return 0;
}

void MP_MICROPHONE_NORMALIZED::update(unsigned long current_time)
{
	normal = 0.8 * normal + 0.2 * (analogRead(pin) - normal);
}

void MP_MICROPHONE_NORMALIZED::printStatus()
{
	Serial.print(F("sound level = "));
	Serial.println(getSoundLevel());
}

double MP_MICROPHONE_NORMALIZED::getSoundLevel()
{
	/* find the range of voltage for some interval */
	double max = 0;
    double min = 1024;
    for (int i=0; i<NORMALIZE_FRAME_COUNT; i++) {
        normal = 0.8 * normal + 0.2 * (analogRead(pin) - normal);
        delayMicroseconds(200);
        if (normal > max) max = normal;
        if (normal < min) min = normal;
	}

	/* High range is high sound level */
	double val = (fabs(max - min) - 100.0) / 3.0;
	if (val > 100) val = 100;
	else if (val < 0) val = 0;
	return val;
}
