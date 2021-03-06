#include "MP_GY906.h"

#define READ_INTERVAL 50

MP_GY906::MP_GY906()
	:mlx(Adafruit_MLX90614())
{
}

int MP_GY906::init()
{
	if (!mlx.begin()) {
		return MP_ERR_CONNECT_DEVICE;
	}
	return MP_ERR_OK;
}

void MP_GY906::update(unsigned long current_time)
{
	if (current_time - lastReadMillis >= READ_INTERVAL) {
		this->celcius = mlx.readObjectTempC();
		lastReadMillis = current_time;
	}
#ifdef ESP8266
    // Since ESP8266 has only 1 processor core, we need to delay for a few ms to allow the network tasks to run.
    // It may be better to use client.flush() but this function is not working in the current version (v2.4.2)
    // of the Arduino core for the ESP8266.
    delay(5);
#endif
}

void MP_GY906::printStatus()
{
	Serial.print(F("temperature (C) = "));
	Serial.println(this->celcius);
}

double MP_GY906::getTemperature()
{
	return this->celcius;
}
