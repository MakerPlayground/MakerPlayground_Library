#include "MP_PCA9685.h"

MP_PCA9685::MP_PCA9685()
{
}

int MP_PCA9685::init()
{
    Wire.begin();
    servo.init(0x7f);
        
    return MP_ERR_OK;
}

void MP_PCA9685::update(unsigned long current_time)
{
}

void MP_PCA9685::printStatus()
{
}

void MP_PCA9685::moveServo(uint8_t channel, int degree)
{
    servo.setAngle(channel, degree);
}