#include "MP_LED_AL.h"

MP_LED_AL::MP_LED_AL(uint8_t pin)
	:pin(pin)
{
}

int MP_LED_AL::init()
{
	pinMode(this->pin, OUTPUT);
	analogWrite(this->pin, 255);
	return MP_ERR_OK;
}

void MP_LED_AL::update(unsigned long current_time) 
{

}

void MP_LED_AL::printStatus() 
{
	Serial.print(F("brightness = "));
	Serial.print(this->brightness);
}

void MP_LED_AL::on(int brightness)
{
	this->brightness = brightness;
	//if microcontroller is a AVR type will do in this part 
#ifdef __AVR__
	//check this pin has PWM or not
	if(digitalPinHasPWM(this->pin))
	{
		analogWrite(this->pin, map(100 - brightness, 0, 100, 0, 255));
	}
	else
	{
		digitalWrite(this -> pin, (100 - brightness) > 0 ? HIGH : LOW);
	}
	//else will do this part
#else
	analogWrite(this->pin, map(100 - brightness, 0, 100, 0, 255));
#endif
}

void MP_LED_AL::off()
{
	this->brightness = 0;
	// digitalWrite and analogWrite don't mix well in ESP32 so we use analogWrite with duty cycle = 0% instead
#ifdef __AVR__
	if(digitalPinHasPWM(this->pin))
	{
		analogWrite(this->pin, 255);
	}
	else
	{
		digitalWrite(this -> pin, HIGH);
	}
#else
	analogWrite(this->pin, 255);
#endif
}