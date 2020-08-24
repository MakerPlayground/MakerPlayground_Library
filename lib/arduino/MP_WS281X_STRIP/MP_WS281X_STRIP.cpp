#include "MP_WS281X_STRIP.h"

MP_WS281X_STRIP::MP_WS281X_STRIP(uint8_t pin, int numPixel)
	: pin(pin)
	, pixels(Adafruit_NeoPixel(numPixel, pin, NEO_RGB + NEO_KHZ800))
{
}

int MP_WS281X_STRIP::init()
{
	pixels.begin();
	pixels.setBrightness(255);
	clear();
	return MP_ERR_OK;
}

void MP_WS281X_STRIP::update(unsigned long current_time)
{
}

void MP_WS281X_STRIP::printStatus()
{
}

void MP_WS281X_STRIP::setColor(int index, int red, int green, int blue)
{
	pixels.setPixelColor(index-1, pixels.Color(red, green, blue));
	pixels.show();
}

void MP_WS281X_STRIP::fillColor(int startIndex, int endIndex, int red, int green, int blue)
{
    uint32_t color = pixels.Color(red, green, blue);
	for (int i=startIndex; i<=endIndex; i++)
	{
	    pixels.setPixelColor(i-1, color);
	}
	pixels.show();
}

void MP_WS281X_STRIP::setBrightness(int brightness)
{
    pixels.setBrightness(brightness);
    pixels.show();
}

void MP_WS281X_STRIP::clear()
{
	pixels.clear();
	pixels.show();
}