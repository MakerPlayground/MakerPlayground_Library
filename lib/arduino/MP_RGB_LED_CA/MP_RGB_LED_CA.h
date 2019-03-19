#ifndef MP_RGB_LED_CA
#define MP_RGB_LED_CA

#include "MP_DEVICE.h"

class MP_RGB_LED_CA
{
public:
	MP_RGB_LED_CA(uint8_t r, uint8_t g, uint8_t b);

	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	void on(int red, int green, int blue, int brightness);
	void off();

private:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	const String tag;
};

#endif
