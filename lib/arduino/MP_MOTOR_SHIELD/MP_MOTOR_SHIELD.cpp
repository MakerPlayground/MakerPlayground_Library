#include "MP_MOTOR_SHIELD.h"

MP_MOTOR_SHIELD::MP_MOTOR_SHIELD()
{
	myMotor = AFMS.getMotor(1);
}

int MP_MOTOR_SHIELD::init()
{
	AFMS.begin();
	direction = RELEASE;
	return ERR_OK;
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

void MP_MOTOR_SHIELD::on(char dir[], double speed)
{
	this->speed = (uint8_t) (speed * 8.0 / 100.0);
	if(strcmp(dir, "Forward") == 0) {
		direction = FORWARD;
	}
	else if(strcmp(dir, "Backward") == 0) {
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

void MP_MOTOR_SHIELD::off()
{
	myMotor->setSpeed(0);
	myMotor->run(RELEASE);
}
