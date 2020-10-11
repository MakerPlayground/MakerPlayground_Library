#include "MP_PAJ7620U2.h"

#define GES_REACTION_TIME 500
#define GES_ENTRY_TIME 800
#define GES_QUIT_TIME 1000

#define READING1 0
#define WAITING 1
#define READING2 2
#define WAIT_OUT 3
#define DONE 4
#define WAIT_RESTART 5

#define MY_GES_WAV_FLAG 256

MP_PAJ7620U2::MP_PAJ7620U2()
    : state(READING1)
{
}

int MP_PAJ7620U2::init()
{
    uint8_t status = paj7620Init();
    if (status != 0) {
        return MP_ERR_CONNECT_DEVICE;
    }
    return MP_ERR_OK;
}

void MP_PAJ7620U2::update(unsigned long current_time)
{
    switch (state)
    {
    case READING1:
        if (!paj7620ReadReg(0x43, 1, &data))
        {
            result = data;
            if ((data == GES_RIGHT_FLAG) || (data == GES_LEFT_FLAG) || (data == GES_UP_FLAG) || (data == GES_DOWN_FLAG))
            {
                end_time = current_time + GES_ENTRY_TIME;
                state = WAITING;
            }
            else if ((data == GES_FORWARD_FLAG) || (data == GES_BACKWARD_FLAG))
            {
                end_time = current_time + GES_QUIT_TIME;
                state = WAIT_OUT;
            }
            else if ((data == GES_CLOCKWISE_FLAG) || (data == GES_COUNT_CLOCKWISE_FLAG))
            {
                state = DONE;
            }
            else
            {
                paj7620ReadReg(0x44, 1, &data);
                if (data == GES_WAVE_FLAG)
                {
                    result = MY_GES_WAV_FLAG;
                }
                else
                {
                    result = 0;
                } 
                state = DONE;
            }
        }
        break;
    case WAITING:
        if (current_time > end_time)
        {
            state = READING2;
        }
        break;
    case READING2:
        if (!paj7620ReadReg(0x43, 1, &data))
        {
            if ((data == GES_FORWARD_FLAG) || (data == GES_BACKWARD_FLAG))
            {
                result = data;
                end_time = current_time + GES_QUIT_TIME;
                state = WAIT_OUT;
            }
            else
            {
                state = DONE;
            }
        }
        break;
    case WAIT_OUT:
        if (current_time > end_time)
        {
            state = DONE;
        }
        break;
    case DONE:
        end_time = current_time + 100;
        state = WAIT_RESTART;
        break;
    case WAIT_RESTART:
        if (current_time > end_time)
        {
            state = READING1;
        }
        break;
    }
}

void MP_PAJ7620U2::printStatus()
{
    if (state == DONE)
    {
        switch (result)
        {
        case GES_RIGHT_FLAG:
            Serial.print(F("Right"));
            break;
        case GES_LEFT_FLAG:
            Serial.print(F("Left"));
            break;
        case GES_UP_FLAG:
            Serial.print(F("Up"));
            break;
        case GES_DOWN_FLAG:
            Serial.print(F("Down"));
            break;
        case GES_FORWARD_FLAG:
            Serial.print(F("Forward"));
            break;
        case GES_BACKWARD_FLAG:
            Serial.print(F("Backward"));
            delay(GES_QUIT_TIME);
            break;
        case GES_CLOCKWISE_FLAG:
            Serial.print(F("Spin Clockwise"));
            break;
        case GES_COUNT_CLOCKWISE_FLAG:
            Serial.print(F("Spin Counter Clockwise"));
            break;
        case MY_GES_WAV_FLAG:
            Serial.print(F("Waving"));
            break;
        }
    }
}

bool MP_PAJ7620U2::isSwipeUp()
{
    return result == GES_UP_FLAG;
}

bool MP_PAJ7620U2::isSwipeDown()
{
    return result == GES_DOWN_FLAG;
}

bool MP_PAJ7620U2::isSwipeLeft()
{
    return result == GES_LEFT_FLAG;
}

bool MP_PAJ7620U2::isSwipeRight()
{
    return result == GES_RIGHT_FLAG;
}

bool MP_PAJ7620U2::isMoveForward()
{
    return result == GES_FORWARD_FLAG;
}

bool MP_PAJ7620U2::isMoveBackward()
{
    return result == GES_BACKWARD_FLAG;
}

bool MP_PAJ7620U2::isSpinClockwise()
{
    return result == GES_CLOCKWISE_FLAG;
}

bool MP_PAJ7620U2::isSpinCounterClockwise()
{
    return result == GES_COUNT_CLOCKWISE_FLAG;
}

bool MP_PAJ7620U2::isWave()
{
    return result == MY_GES_WAV_FLAG;
}

bool MP_PAJ7620U2::isNotDetected()
{
    return result == 0;
}