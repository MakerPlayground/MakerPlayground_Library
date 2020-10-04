#include "MP_GROVE_LEDBUTTON.h"

MP_GROVE_LEDBUTTON::MP_GROVE_LEDBUTTON(uint8_t ledPin, uint8_t buttonPin)
	: ledPin(ledPin)
	, buttonPin(buttonPin)
{
}

int MP_GROVE_LEDBUTTON::init()
{
    pinMode(ledPin, OUTPUT);
	pinMode(buttonPin, INPUT_PULLUP);
    checkpoint = millis();
	return MP_ERR_OK;
}

void MP_GROVE_LEDBUTTON::update(unsigned long current_time)
{
    if (state == NOTHING && isPress() && current_time >= 30 + checkpoint) {
        state = PRESSED;
    }
    if (state == PRESSED && isNotPress()) {
        state = JUST_RELEASE;
        checkpoint = millis();
    }
    if (state == JUST_RELEASE && current_time >= 150 + checkpoint) {
        state = NOTHING;
    }
}

void MP_GROVE_LEDBUTTON::printStatus() 
{
	Serial.print(F("Button is "));
	Serial.println((digitalRead(buttonPin) == LOW) ? F("pressed"): F("not pressed"));
}

bool MP_GROVE_LEDBUTTON::isPress()
{
    return (digitalRead(buttonPin) == LOW);
}

bool MP_GROVE_LEDBUTTON::isPressAndRelease()
{
    return state == JUST_RELEASE;
}

bool MP_GROVE_LEDBUTTON::isNotPress()
{
    return (digitalRead(buttonPin) == HIGH);
}

void MP_GROVE_LEDBUTTON::on(int brightness)
{
	//if microcontroller is a AVR type will do in this part
#ifdef __AVR__
	//check this pin has PWM or not
	if(digitalPinHasPWM(this->ledPin))
	{
		analogWrite(this->ledPin, map(brightness, 0, 100, 0, 255));
	}
	else
	{
		digitalWrite(this->ledPin, brightness > 0 ? HIGH : LOW);
	}
	//else will do this part
#else
	analogWrite(this->ledPin, map(brightness, 0, 100, 0, 255));
#endif
}

void MP_GROVE_LEDBUTTON::off()
{
	// digitalWrite and analogWrite don't mix well in ESP32 so we use analogWrite with duty cycle = 0% instead
#ifdef __AVR__
	if(digitalPinHasPWM(this->ledPin))
	{
		analogWrite(this->ledPin, 0);
	}
	else
	{
		digitalWrite(this->ledPin, LOW);
	}
#else
	analogWrite(this->ledPin, 0);
#endif
}