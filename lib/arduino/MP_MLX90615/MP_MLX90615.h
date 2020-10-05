#ifndef MP_MLX90615_H
#define MP_MLX90615_H

#include "MP_DEVICE.h"
#include <mlx90615.h>


class MP_MLX90615
{
public:
	MP_MLX90615(uint8_t mode);

	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getTemperature();

private:
	MLX90615 mlx;
	uint8_t mode;
	
	double celcius;
};

#endif
