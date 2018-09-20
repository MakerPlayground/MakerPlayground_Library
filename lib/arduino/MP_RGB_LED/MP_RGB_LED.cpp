#include "MP_RGB_LED.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* MP_RGB_LED::ERRORS = errors_p;

MP_RGB_LED::MP_RGB_LED(uint8_t data, uint8_t clk)
	:data(data)
	,clk(clk)
{
}

int MP_RGB_LED::init()
{
	digitalWrite(data, LOW);
	pinMode(data, OUTPUT);
	digitalWrite(clk, LOW);
	pinMode(clk,OUTPUT);
	return 0;
}

void MP_RGB_LED::update(unsigned long current_time) 
{

}

void MP_RGB_LED::printStatus() 
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

void MP_RGB_LED::on(int red, int green, int blue, int brightness)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->brightness = brightness;
	startFrame();
	sendColor(red, green, blue, ((float) brightness/100.0)*31);
	endFrame(1);
}

void MP_RGB_LED::off()
{
	this->brightness = 0;
	startFrame();
	sendColor(0,0,0,0);
	endFrame(1);
}

void MP_RGB_LED::startFrame()
{
	digitalWrite(data,LOW);
	digitalWrite(clk,LOW);
	transfer(0);
	transfer(0);
	transfer(0);
	transfer(0);
}

void MP_RGB_LED::sendColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness)
{
	transfer(0b11100000 | brightness);
	transfer(blue);
	transfer(green);
	transfer(red);
}

void MP_RGB_LED::endFrame(uint16_t count)
{
	transfer(0xFF);
	for (uint16_t i = 0 ; i < 5 + count / 16; i++)
	{
		transfer(0);
	}
}

void MP_RGB_LED::transfer(uint8_t b)
{
	digitalWrite(data, b >> 7 & 1);
	digitalWrite(clk, HIGH);
	digitalWrite(clk, LOW);
	digitalWrite(data, b >> 6 & 1);
	digitalWrite(clk, HIGH);
	digitalWrite(clk, LOW);
	digitalWrite(data, b >> 5 & 1);
	digitalWrite(clk, HIGH);
	digitalWrite(clk, LOW);
	digitalWrite(data, b >> 4 & 1);
	digitalWrite(clk, HIGH);
	digitalWrite(clk, LOW);
	digitalWrite(data, b >> 3 & 1);
	digitalWrite(clk, HIGH);
	digitalWrite(clk, LOW);
	digitalWrite(data, b >> 2 & 1);
	digitalWrite(clk, HIGH);
	digitalWrite(clk, LOW);
	digitalWrite(data, b >> 1 & 1);
	digitalWrite(clk, HIGH);
	digitalWrite(clk, LOW);
	digitalWrite(data, b >> 0 & 1);
	digitalWrite(clk, HIGH);
	digitalWrite(clk, LOW);
}
