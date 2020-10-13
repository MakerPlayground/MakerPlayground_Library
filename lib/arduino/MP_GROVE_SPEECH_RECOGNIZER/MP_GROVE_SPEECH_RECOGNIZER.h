#ifndef MP_GROVE_SPEECH_RECOGNIZER_H
#define MP_GROVE_SPEECH_RECOGNIZER_H

#include "MP_DEVICE.h"
#include "SoftwareSerial.h"

class MP_GROVE_SPEECH_RECOGNIZER
{
public:
	MP_GROVE_SPEECH_RECOGNIZER(uint8_t tx, uint8_t rx);
	int init();
	void update(unsigned long current_time);
	void printStatus();

    bool recognize(const char* word);

private:
    SoftwareSerial softSerial;
    char cmd;
    unsigned long latestDetectTime;
};

#endif
