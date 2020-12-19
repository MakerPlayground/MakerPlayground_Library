#include "ESP32_Polyfill.h"

#ifdef ESP32

const uint8_t channelCount = 16;
// channel 0, 1, 8, 9 may be used by the camera so we reserve them by set the owner to 254
uint8_t channelOwner[channelCount] = {254, 254, 255, 255, 255, 255, 255, 255, 254, 254, 255, 255, 255, 255, 255, 255};
bool channelInitialized[channelCount] = {false};

uint8_t getChannel(uint8_t pin)
{
    uint8_t channel = 0;
    // find channel previously allocate for this pin
    for (channel = 0; channel < channelCount; channel++)
        if (channelOwner[channel] == pin)
            return channel;
    // otherwise, we find a free and reserved channel for this pin
    for (channel = 0; channel < channelCount; channel++) {
        if (channelOwner[channel] == 255) {
            channelOwner[channel] = pin;
            return channel;
        }
    }
    // if we reach this line, every channels have been allocated thus we return error (channelCount)
    return channelCount;
}

void analogWrite(uint8_t pin, uint16_t value)
{
    uint8_t channel = getChannel(pin);
    if (channel == channelCount) {
        // just turn on or off without generating PWM if the channel is not available
        digitalWrite(pin, (value > 127 ? HIGH : LOW));
        return;
    }

    if (value == 0 || value == 255)
    {
        if (!channelInitialized[channel])
        {
            digitalWrite(pin, (value == 255) ? HIGH : LOW);
        }
        else
        {
            digitalWrite(pin, (value == 255) ? HIGH : LOW);
			ledcDetachPin(pin);
            channelInitialized[channel] = false;
        }
    }
    else
    {
        if (!channelInitialized[channel]) 
        {
            channelInitialized[channel] = true;
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

    if (!channelInitialized[channel]) 
    {
        channelInitialized[channel] = true;
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

    if (!channelInitialized[channel])
    {
        channelInitialized[channel] = true;
        ledcSetup(channel, 1000, 8);    // any value can be used as ledcWriteTone will override them anyway
        ledcWriteTone(channel, 0);
        ledcAttachPin(pin, channel);
    }
    else
    {
        ledcWriteTone(channel, 0);
        ledcDetachPin(pin);
        channelInitialized[channel] = false;
    }
}

#endif