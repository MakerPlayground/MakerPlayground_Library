#ifndef MP_MOTOR_SHIELD_H
#define MP_MOTOR_SHIELD_H

#include <Arduino.h>
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
	static const char* const* ERRORS;

	void on(char dir[], uint8_t speed);
	void reverse();
	void set_speed(uint8_t speed);
	void off();

private:
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor;

	uint8_t speed;
	uint8_t direction;
};

#endif
