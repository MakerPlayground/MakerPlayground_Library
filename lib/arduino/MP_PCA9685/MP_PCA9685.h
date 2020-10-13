#ifndef MP_PCA9685_H
#define MP_PCA9685_H

#include "MP_DEVICE.h"
#include "PCA9685.h"
#include <Wire.h>

class MP_PCA9685
{
public:

	MP_PCA9685();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void moveServo(uint8_t channel, int degree);

private:
	ServoDriver servo;
};
#endif
