#include "MP_SERVO.h"

MP_SERVO::MP_SERVO(uint8_t pin)
  : pin(pin)
{
}

int MP_SERVO::init()
{
    this->degree = 0;
    myservo.attach(pin);
    return ERR_OK;
}

void MP_SERVO::update(unsigned long current_time) 
{

}

void MP_SERVO::printStatus()
{
    Serial.print(F("current angle = "));
    Serial.println(this->degree);
}

void MP_SERVO::moveto(int degree)
{
    this->degree = degree;
	myservo.write(degree);
}
