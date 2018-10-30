#include "ESP32_Polyfill.h"

#ifdef ESP32

const uint8_t pinList[] = {13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27};
constexpr uint8_t channelCount = sizeof(pinList) / sizeof(pinList[0]);

bool pinUsed[channelCount] = {false};

// find ledc channel for a pin
uint8_t getChannel(uint8_t pin)
{
    uint8_t channel = 0;
    for (channel = 0; channel < channelCount; channel++)
        if (pinList[channel] == pin)
            break;
    return channel;
}

void analogWrite(uint8_t pin, uint16_t value)
{
    // do nothing if channel can't be found
    uint8_t channel = getChannel(pin);
    if (channel == channelCount)
        return;

    if (value == 0 || value == 255)
    {
        if (!pinUsed[channel])
        {
            digitalWrite(pin, (value == 255) ? HIGH : LOW);
        }
        else
        {
            digitalWrite(pin, (value == 255) ? HIGH : LOW);
			ledcDetachPin(pin);
            pinUsed[channel] = false;
        }
    }
    else
    {
        if (!pinUsed[channel]) 
        {
            pinUsed[channel] = true;
            ledcSetup(channel, 1000, 8);    // 1KHz 8bit
            ledcWrite(channel, value);
            ledcAttachPin(pin, channel);
        }
        else
        {
            ledcWrite(channel, value);
        }
    }
}

void tone(uint8_t pin, uint16_t freq)
{
    // do nothing if channel can't be found
    uint8_t channel = getChannel(pin);
    if (channel == channelCount)
        return;

    if (!pinUsed[channel]) 
    {
        pinUsed[channel] = true;
        ledcSetup(channel, 1000, 8);    // any value can be used as ledcWriteTone will override them anyway
        ledcWriteTone(channel, freq);
        ledcAttachPin(pin, channel);
    }
    else
    {
        ledcWriteTone(channel, freq);
    }
}

void noTone(uint8_t pin)
{
    // do nothing if channel can't be found
    uint8_t channel = getChannel(pin);
    if (channel == channelCount)
        return;

    if (!pinUsed[channel])
    {
        pinUsed[channel] = true;
        ledcSetup(channel, 1000, 8);    // any value can be used as ledcWriteTone will override them anyway
        ledcWriteTone(channel, 0);
        ledcAttachPin(pin, channel);
    }
    else
    {
        ledcWriteTone(channel, 0);
    }
}

#endif