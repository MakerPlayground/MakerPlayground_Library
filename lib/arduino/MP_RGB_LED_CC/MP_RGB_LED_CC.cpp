#include "MP_RGB_LED_CC.h"

MP_RGB_LED_CC::MP_RGB_LED_CC(uint8_t r, uint8_t g, uint8_t b)
	:r(r)
	,g(g)
	,b(b)
{
}

int MP_RGB_LED_CC::init()
{
	pinMode(r, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(b, OUTPUT);
	return MP_ERR_OK;
}

void MP_RGB_LED_CC::update(unsigned long current_time) 
{

}

void MP_RGB_LED_CC::printStatus() 
{
	Serial.print(F("red = "));
	Serial.println(this->red);
	Serial.print(F("green = "));
	Serial.println(this->green);
	Serial.print(F("blue = "));
	Serial.println(this->blue);
	Serial.print(F("brightness = "));
	Serial.println(this->brightness);
}

void MP_RGB_LED_CC::on(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->brightness = brightness;
	analogWrite(r, (red * brightness) / 100.0);
	analogWrite(g, (green * brightness) / 100.0);
	analogWrite(b, (blue * brightness) / 100.0);
}

void MP_RGB_LED_CC::off()
{
	analogWrite(r, 0);
	analogWrite(g, 0);
	analogWrite(b, 0);
}
