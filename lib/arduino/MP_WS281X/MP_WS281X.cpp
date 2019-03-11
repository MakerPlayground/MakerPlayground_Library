#include "MP_WS281X.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_WS281X::ERRORS = errors_p;

#define NUMPIXELS 1

MP_WS281X::MP_WS281X(uint8_t pin)
	: pin(pin)
	, pixels(Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800))
{
}

int MP_WS281X::init()
{
	pixels.begin();
	off();
	return 0;
}

void MP_WS281X::update(unsigned long current_time) 
{

}

void MP_WS281X::printStatus() 
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

void MP_WS281X::on(int red, int green, int blue, int brightness)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->brightness = brightness;
	pixels.setBrightness(brightness);
	pixels.setPixelColor(0, pixels.Color(red, green, blue));
	pixels.show();
}

void MP_WS281X::off()
{
	this->brightness = 0;
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	pixels.setBrightness(0);
	pixels.setPixelColor(0, pixels.Color(0, 0, 0));
	pixels.show(); // Initialize all pixels to 'off'
}