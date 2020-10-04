#include "MP_CHAINABLELED_P9813.h"

MP_CHAINABLELED_P9813::MP_CHAINABLELED_P9813(uint8_t clkPin, uint8_t dataPin, int numPixel)
	: leds(clkPin, dataPin, numPixel)
	, numPixel(numPixel)
	, brightness(100)
{
}

int MP_CHAINABLELED_P9813::init()
{
    leds.init();
	return MP_ERR_OK;
}

void MP_CHAINABLELED_P9813::update(unsigned long current_time) 
{
}

void MP_CHAINABLELED_P9813::printStatus()
{
}

void MP_CHAINABLELED_P9813::setColor(int index, int red, int green, int blue)
{
	leds.setColorRGB(index-1, red * this->brightness / 100.0, green * this->brightness / 100.0, blue * this->brightness / 100.0);
}

void MP_CHAINABLELED_P9813::fillColor(int startIndex, int endIndex, int red, int green, int blue)
{
	for (int i=startIndex; i<=endIndex; i++)
	{
	    leds.setColorRGB(i-1, red * this->brightness / 100.0, green * this->brightness / 100.0, blue * this->brightness / 100.0);
	}
}

void MP_CHAINABLELED_P9813::setBrightness(int brightness)
{
    this->brightness = brightness;
}

void MP_CHAINABLELED_P9813::clear()
{
    for (int i=0; i<numPixel; i++)
    {
        leds.setColorRGB(i, 0, 0, 0);
    }
}
