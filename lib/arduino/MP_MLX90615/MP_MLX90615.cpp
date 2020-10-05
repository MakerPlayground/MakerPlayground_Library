#include "MP_MLX90615.h"

#define UPDATE_INTERVAL 50

MP_MLX90615::MP_MLX90615(uint8_t mode)
	:mlx(MLX90615())
  , mode(mode)
{
}

int MP_MLX90615::init()
{
	this->celcius = 0;
	mlx.begin();
	return MP_ERR_OK;
}

void MP_MLX90615::update(unsigned long current_time)
{
  if (mode == 0) { // Object Temp
	  this->celcius = mlx.get_object_temp();
  } else if (mode == 1) {
    this->celcius = mlx.get_ambient_temp();
  }
}

void MP_MLX90615::printStatus()
{
	Serial.print(F(" , temperature (C) = "));
	Serial.println(this->celcius);
}

double MP_MLX90615::getTemperature()
{
	return this->celcius;
}