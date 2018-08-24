#include "MP_RGB_LED_CA.h"

MP_RGB_LED_CA::MP_RGB_LED_CA(uint8_t r, uint8_t g, uint8_t b, const String &tag)
	:r(r)
	,g(g)
	,b(b)
	,tag(tag)
{
}

void MP_RGB_LED_CA::init()
{
	pinMode(r, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(b, OUTPUT);
}

void MP_RGB_LED_CA::on(int red, int green, int blue, int brightness)
{
	red = 255 - (red * brightness) / 100.0;
	green = 255 - (green * brightness) / 100.0;
	blue = 255 - (blue * brightness) / 100.0;
	analogWrite(r, red);
	analogWrite(g, green);
	analogWrite(b, blue);
}

void MP_RGB_LED_CA::off()
{
	digitalWrite(r, LOW);
	digitalWrite(g, LOW);
	digitalWrite(b, LOW);
}
