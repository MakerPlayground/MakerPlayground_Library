#include "MP_MICROPHONE.h"

#define SAMPLEWINDOW 400

MP_MICROPHONE::MP_MICROPHONE(uint8_t pin)
	:pin(pin)
{
}

int MP_MICROPHONE::init()
{
	this->soundLevel = 0;
	signalMin = 1024;
	signalMax = 0;
	pinMode(pin, INPUT);
	return MP_ERR_OK;
}

void MP_MICROPHONE::update(unsigned long current_time)
{
	// reset data every SAMPLEWINDOW mS
	if (current_time - startMillis < SAMPLEWINDOW)
	{
		signalMax = 0;
		signalMin = 1024;
		for (int i=0; i<10; i++) {
			int sample = analogRead(pin);
			if (sample < 1024)  // toss out spurious readings
			{
				signalMax = sample > signalMax ? sample : signalMax; // save just the max levels
				signalMin = sample < signalMin ? sample : signalMin; // save just the min levels
			}
		}
		startMillis = current_time;
	}

	int sample = analogRead(pin);
	if (sample < 1024)  // toss out spurious readings
	{
		signalMax = sample > signalMax ? sample : signalMax; // save just the max levels
		signalMin = sample < signalMin ? sample : signalMin; // save just the min levels
	}

	soundLevel = ((signalMax - signalMin) * 100.0) / 1023;  // peak-peak amplitude
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
