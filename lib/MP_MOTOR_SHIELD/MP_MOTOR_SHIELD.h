#ifndef MP_MOTOR_SHIELD_H
#define MP_MOTOR_SHIELD_H

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_MotorShield.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"

class MP_MOTOR_SHIELD
{
public:
	MP_MOTOR_SHIELD(const String &tag);
	void init();
	void on(char dir[], uint8_t speed);
	void reverse();
	void set_speed(uint8_t speed);
	void off();

private:
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor;
	uint8_t pin=0;
	const String tag;
};

#endif
