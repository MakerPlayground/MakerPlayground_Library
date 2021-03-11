#include "MP_MICROPHONE.h"

#define SAMPLEWINDOW 200

MP_MICROPHONE::MP_MICROPHONE(uint8_t pin)
	: pin(pin)
{
}

int MP_MICROPHONE::init()
{
	soundLevel = 0;
	startMillis = 0;
	signalMin = 1024;
	signalMax = 0;
	pinMode(pin, INPUT);
	return MP_ERR_OK;
}

void MP_MICROPHONE::update(unsigned long current_time)
{
    if (current_time - startMillis > SAMPLEWINDOW)
    {
        // peak-peak amplitude as percentage of the full-range
        soundLevel = signalMax < signalMin ? 0 : ((signalMax - signalMin) * 100.0) / 1023;
        // reset min, max and start time
        signalMin = 1024;
        signalMax = 0;
        startMillis = current_time;
    }

    int sample = analogRead(pin);
    if (sample > signalMax)
    {
        signalMax = sample;
    }
    if (sample < signalMin)
    {
        signalMin = sample;
    }
}

void MP_MICROPHONE::printStatus()
{
	Serial.print(F("sound level = "));
	Serial.println(this->soundLevel);
}

double MP_MICROPHONE::getSoundLevel()
{
	return this->soundLevel;
}
