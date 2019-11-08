#include "MP_WS281X_GRB.h"

#define NUMPIXELS 1

MP_WS281X_GRB::MP_WS281X_GRB(uint8_t pin)
	: pin(pin)
	, pixels(Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800))
{
}

int MP_WS281X_GRB::init()
{
	pixels.begin();
	off();
	return ERR_OK;
}

void MP_WS281X_GRB::update(unsigned long current_time) 
{

}

void MP_WS281X_GRB::printStatus() 
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

void MP_WS281X_GRB::on(int red, int green, int blue, int brightness)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->brightness = brightness;
	pixels.setBrightness(brightness);
	pixels.setPixelColor(0, pixels.Color(red, green, blue));
	pixels.show();
}

void MP_WS281X_GRB::off()
{
	this->brightness = 0;
	this->red = 0;
	this->green = 0;
	this->blue = 0;
	pixels.setBrightness(0);
	pixels.setPixelColor(0, pixels.Color(0, 0, 0));
	pixels.show(); // Initialize all pixels to 'off'
}