#ifndef MP_MOTOR_SHIELD_H
#define MP_MOTOR_SHIELD_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "Adafruit_MotorShield.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"

class MP_MOTOR_SHIELD
{
public:
	MP_MOTOR_SHIELD();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	void motorOn(uint8_t ch,  uint8_t dir, double speed);
	void reverse();
	void set_speed(uint8_t speed);
	void motorOff(uint8_t ch);

private:
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor;

	uint8_t speed;
	uint8_t direction;
};

#endif
