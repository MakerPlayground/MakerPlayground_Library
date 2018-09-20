#ifndef MP_RGB_LED_H
#define MP_RGB_LED_H

#include <Arduino.h>
class MP_RGB_LED
{
public:
	MP_RGB_LED(uint8_t data, uint8_t clk);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	void on(int red, int green, int blue, int brightness);
	void off();

private:
	void startFrame();
	void sendColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness = 31);
	void endFrame(uint16_t count);
	void transfer(uint8_t b);

	uint8_t data;
	uint8_t clk;
	int red;
	int green;
	int blue;
	int brightness;
};

#endif
