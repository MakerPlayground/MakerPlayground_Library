#include "MP_MOTOR_SHIELD.h"

MP_MOTOR_SHIELD::MP_MOTOR_SHIELD()
{

}

int MP_MOTOR_SHIELD::init()
{
	AFMS.begin();
	direction = RELEASE;
	myMotor = AFMS.getMotor(1);
	return MP_ERR_OK;
}

void MP_MOTOR_SHIELD::update(unsigned long current_time)
{

}

void MP_MOTOR_SHIELD::printStatus()
{
	Serial.print(F("speed = "));
	Serial.println(this->speed);

	Serial.print(F("direction = "));
	if (this->direction == FORWARD) {
		Serial.println("FORWARD");
	}
	else if (this->direction == BACKWARD) {
		Serial.println("BACKWARD");
	}
	else if (this->direction == RELEASE) {
		Serial.println("RELEASE");
	}
}


// dir == 1 Forward
// dir == 0 Backward
void MP_MOTOR_SHIELD::motorOn(uint8_t ch,  uint8_t dir, double speed)
{
	myMotor = AFMS.getMotor(ch);
	this->speed = (uint8_t) (speed * 8.0 / 100.0);
	if(dir == 1) {
		direction = FORWARD;
	}
	else if(dir == 0) {
		direction = BACKWARD;
	}
	else {
		direction = RELEASE;
		this->speed = 0;
	}
	myMotor->setSpeed(speed);
	myMotor->run(direction);
}

// void MP_MOTOR_SHIELD::reverse()
// {
// 	if(direction == FORWARD)
// 	{
// 		direction = BACKWARD;
// 		myMotor->run(direction);
// 	}
// 	else if(direction == BACKWARD)
// 	{
// 		direction = FORWARD;
// 		myMotor->run(direction);
// 	}
// }

// void MP_MOTOR_SHIELD::set_speed(uint8_t speed)
// {
// 	this->speed = speed;
// 	myMotor->setSpeed(speed);
// }

void MP_MOTOR_SHIELD::motorOff(uint8_t ch)
{
	myMotor = AFMS.getMotor(ch);
	myMotor->setSpeed(0);
	myMotor->run(RELEASE);
}
