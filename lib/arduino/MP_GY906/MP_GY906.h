#ifndef MP_GY906_H
#define MP_GY906_H

#include "MP_DEVICE.h"
#include <Adafruit_MLX90614.h>

class MP_GY906
{
public:
	MP_GY906();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getTemperature();

private:
	Adafruit_MLX90614 mlx;
	unsigned long lastReadMillis = 0;
	double celcius = 25.0;
};

#endif
