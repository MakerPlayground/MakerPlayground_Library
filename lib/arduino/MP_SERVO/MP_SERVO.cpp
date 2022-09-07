#include "MP_SERVO.h"

#ifdef ESP32
static int ledCChannel = 15;
#endif

MP_SERVO::MP_SERVO(uint8_t pin)
  : pin(pin)
{
}

int MP_SERVO::init()
{
    this->degree = 0;
#ifdef ESP32
    // TODO: proper fix after arduino esp32 core version 2.0.5 is released
    // // reserve ESP32's LEDC channel by calling analogWrite with duty cycle 0 (servo should not move)
    // analogWrite(pin, 0);
    // myservo.attach(pin, analogGetChannel(pin));
    myservo.attach(pin, ledCChannel);
    ledCChannel--;
#else
    myservo.attach(pin);
#endif
    return MP_ERR_OK;
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
