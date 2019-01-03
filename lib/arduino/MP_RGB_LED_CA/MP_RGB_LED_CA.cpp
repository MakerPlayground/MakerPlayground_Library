#include "MP_RGB_LED_CA.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_RGB_LED_CA::ERRORS = errors_p;

MP_RGB_LED_CA::MP_RGB_LED_CA(uint8_t r, uint8_t g, uint8_t b)
	:r(r)
	,g(g)
	,b(b)
{
}

void MP_RGB_LED_CA::init()
{
	pinMode(r, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(b, OUTPUT);
}

void MP_RGB_LED_CA::update(unsigned long current_time) 
{

}

void MP_RGB_LED_CA::printStatus() 
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

void MP_RGB_LED_CA::on(int red, int green, int blue, int brightness)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->brightness = brightness;
	analogWrite(r, 255 - (red * brightness) / 100.0);
	analogWrite(g, 255 - (green * brightness) / 100.0);
	analogWrite(b, 255 - (blue * brightness) / 100.0);
}

void MP_RGB_LED_CA::off()
{
	digitalWrite(r, HIGH);
	digitalWrite(g, HIGH);
	digitalWrite(b, HIGH);
}
