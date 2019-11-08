#include "MP_WS281X_STRIP_GRB.h"

MP_WS281X_STRIP_GRB::MP_WS281X_STRIP_GRB(uint8_t pin, int numPixel)
	: pin(pin)
	, pixels(Adafruit_NeoPixel(numPixel, pin, NEO_GRB + NEO_KHZ800))
{
}

int MP_WS281X_STRIP_GRB::init()
{
	pixels.begin();
	pixels.setBrightness(255);
	clear();
	return ERR_OK;
}

void MP_WS281X_STRIP_GRB::update(unsigned long current_time)
{
}

void MP_WS281X_STRIP_GRB::printStatus()
{
}

void MP_WS281X_STRIP_GRB::setColor(int index, int red, int green, int blue)
{
	pixels.setPixelColor(index-1, pixels.Color(red, green, blue));
	pixels.show();
}

void MP_WS281X_STRIP_GRB::fillColor(int startIndex, int endIndex, int red, int green, int blue)
{
    uint32_t color = pixels.Color(red, green, blue);
	for (int i=startIndex; i<=endIndex; i++)
	{
	    pixels.setPixelColor(i-1, color);
	}
	pixels.show();
}

void MP_WS281X_STRIP_GRB::setBrightness(int brightness)
{
    pixels.setBrightness(brightness);
    pixels.show();
}

void MP_WS281X_STRIP_GRB::clear()
{
	pixels.clear();
	pixels.show();
}