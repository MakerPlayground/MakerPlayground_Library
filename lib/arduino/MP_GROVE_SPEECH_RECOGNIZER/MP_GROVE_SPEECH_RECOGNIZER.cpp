#define TIMEOUT 1000

#include "MP_GROVE_SPEECH_RECOGNIZER.h"

const char *voiceBuffer[] =
{
    "Turn on the light",
    "Turn off the light",
    "Play music",
    "Pause",
    "Next",
    "Previous",
    "Up",
    "Down",
    "Turn on the TV",
    "Turn off the TV",
    "Increase temperature",
    "Decrease temperature",
    "What's the time",
    "Open the door",
    "Close the door",
    "Left",
    "Right",
    "Stop",
    "Start",
    "Mode 1",
    "Mode 2",
    "Go",
};

MP_GROVE_SPEECH_RECOGNIZER::MP_GROVE_SPEECH_RECOGNIZER(uint8_t tx, uint8_t rx)
	: softSerial(tx, rx)
	, cmd(255)
	, latestDetectTime(0)
{
}

int MP_GROVE_SPEECH_RECOGNIZER::init()
{
    softSerial.begin(9600);
	return MP_ERR_OK;
}

void MP_GROVE_SPEECH_RECOGNIZER::update(unsigned long current_time) 
{
    if (softSerial.available())
    {
        cmd = softSerial.read();
        latestDetectTime = current_time;
    }

    if (latestDetectTime - current_time > TIMEOUT)
    {
        cmd = 255;
    }
}

void MP_GROVE_SPEECH_RECOGNIZER::printStatus() 
{
}

bool MP_GROVE_SPEECH_RECOGNIZER::recognize(const char* word)
{
    if (cmd != 255)
    {
        bool result = (strcmp(word, voiceBuffer[cmd - 1]) == 0);
        return result;
    }
    return false;
}