#include "MP_TCS34725.h"

float MAX (float r, float g, float b);
float MIN (float r, float g, float b);
void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );

MP_TCS34725::MP_TCS34725()
{
}

int MP_TCS34725::init()
{
	if (!tcs.begin()) {
		return MP_ERR_CONNECT_DEVICE;
	}
	this->end_time = 0;
	this->update(0);
	return MP_ERR_OK;
}

void MP_TCS34725::update(unsigned long current_time)
{
	if (current_time == 0 || current_time - end_time > 50) {
		tcs.setInterrupt(false);      // turn on LED
		delay(60);  // takes 50ms to read 
		tcs.getRawData(&red, &green, &blue, &clear);
		tcs.setInterrupt(true);  // turn off LED

		double r, g, b;
		r = 255.0 * red / clear; 
		g = 255.0 * green / clear; 
		b = 255.0 * blue / clear;

		rgb2hsv(r, g, b, &h, &s, &v);

		red = (uint16_t) r;
		green = (uint16_t) g;
		blue = (uint16_t) b;

		color_code = hsv2ColorCode(h, s, v);

		end_time = current_time;
	}
}

void MP_TCS34725::printStatus()
{
	Serial.print(F("Color: "));
	Serial.print((int)this->red, HEX);
	Serial.print((int)this->green, HEX);
	Serial.print((int)this->blue, HEX);
	Serial.println();

	Serial.print(F("R = "));
	Serial.println(this->red);

	Serial.print(F("G = "));
	Serial.println(this->green);

	Serial.print(F("B = "));
	Serial.println(this->blue);

	Serial.print(F("H = "));
	Serial.println(this->h);

	Serial.print(F("S = "));
	Serial.println(this->s);

	Serial.print(F("V = "));
	Serial.println(this->v);
}

bool MP_TCS34725::isColor(uint8_t color)
{
	return color == color_code;
}

double MP_TCS34725::getRed() {
	return red;
}

double MP_TCS34725::getGreen() {
	return green;
}

double MP_TCS34725::getBlue() {
	return blue;
}

double MP_TCS34725::getHue() {
	return h;
}

double MP_TCS34725::getSaturation() {
	return s;
}

double MP_TCS34725::getValue() {
	return v;
}

// range of r, g, b is [0, 255]
// range of h is [0, 360]
// range of s is [0, 255]
// range of v is [0, 255]
void MP_TCS34725::rgb2hsv(double r, double g, double b, double *h, double *s, double *v )
{
	float min, max, delta;

	min = r < g ? r : g;
	min = min  < b ? min  : b;

	max = r > g ? r : g;
	max = max  > b ? max  : b;

	*v = max;
	delta = max - min;

	if (delta < 0.00001)
	{
		*s = 0;
		*h = 0; // undefined, maybe nan?
		return;
	}
	if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
		*s = (delta / max) * 255.0;
	} 
	else {
		// if max is 0, then r = g = b = 0
		// s = 0, h is undefined
		*s = 0.0;
		*h = NAN;                      // its now undefined
		return;
	}
	if( r >= max )                         // > is bogus, just keeps compilor happy
		*h = ( g - b ) / delta;        // between yellow & magenta
	else if( g >= max )
		*h = 2.0 + ( b - r ) / delta;  // between cyan & yellow
	else
		*h = 4.0 + ( r - g ) / delta;  // between magenta & cyan

	*h *= 60.0;                        // degrees

	if( *h < 0.0 )
		*h += 360.0;

	return;
}

uint8_t MP_TCS34725::hsv2ColorCode(double h, double s, double v) {
	uint8_t color_code;
	if (s < 50 && v > 80) {
		color_code = 7;
	} else if (s > 125 && v < 100) {
		color_code = 9;
	} else if(h>=330 || h<15) {
		color_code = 0;
	} else if(h>=15 && h<25) {
		color_code = 5;
	} else if(h>=25 && h<75) {
		color_code = 8;
	} else if(h>=75 && h<165) {
		color_code = 1;
	} else if(h>=165 && h<220) {
		color_code = 3;
	} else if(h>=220 && h<235) {
		color_code = 2;
	} else if(h>=235 && h<270) {
		color_code = 6;
	} else if(h>=270 && h<330) {
		color_code = 4;
	} else {
		color_code = -1;
	}
	return color_code;
}