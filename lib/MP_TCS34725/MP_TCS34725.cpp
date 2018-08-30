#include "MP_TCS34725.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "No TCS34725 found ... check your connections"
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_TCS34725::ERRORS = errors_p;

float MAX (float r, float g, float b);
float MIN (float r, float g, float b);
void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );

MP_TCS34725::MP_TCS34725()
{
}

int MP_TCS34725::init()
{
	if (!tcs.begin()) {
		return 1;
	}
	this->end_time = 0;
	this->update(0);
	return 0;
}

void MP_TCS34725::update(unsigned long current_time)
{
	if (current_time == 0 || current_time - end_time > 50) {
		tcs.setInterrupt(false);      // turn on LED
		delay(60);  // takes 50ms to read 
		tcs.getRawData(&red, &green, &blue, &clear);
		tcs.setInterrupt(true);  // turn off LED

		// Figure out some basic hex code for visualization
		float r, g, b;
		r = ((float) red) / clear; 
		g = ((float) green) / clear; 
		b = ((float) blue) / clear;

		RGBtoHSV(r, g, b, &h, &s, &v);

		this->red = r * 256;
		this->green = g * 256;
		this->blue = b * 256;

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

int MP_TCS34725::isColor(char color[])
{
	if (strcmp(color, "Red") == 0) {
		return (h < 60 || h > 300);
	} else if (strcmp(color, "Green") == 0) {
		return (h < 180 && h > 60);
	} else if (strcmp(color, "Blue") == 0) {
		return (h < 320 && h > 180);
	} else {
		return 0;
	}
}

float MAX (float r, float g, float b)
{
	float temp = r;
	if (g > temp)
		temp = g;
	if (b > temp)
		temp = b;
	return temp;
}

float MIN (float r, float g, float b)
{
	float temp = r;
	if (g < temp)
		temp = g;
	if (b < temp)
		temp = b;
	return temp;
}

void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
{
	float min, max, delta;
	min = MIN( r, g, b );
	max = MAX( r, g, b );
	*v = max;       // v
	delta = max - min;

	if( max != 0 )
		*s = delta / max;   // s
	else {
		// r = g = b = 0    // s = 0, v is undefined
		*s = 0;
		*h = -1;
		return;
	}
	if( r == max )
		*h = ( g - b ) / delta;   // between yellow & magenta
	else if( g == max )
		*h = 2 + ( b - r ) / delta; // between cyan & yellow
	else
		*h = 4 + ( r - g ) / delta; // between magenta & cyan
	*h *= 60;       // degrees
	if( *h < 0 )
		*h += 360;
}