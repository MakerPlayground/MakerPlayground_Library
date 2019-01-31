#ifndef MP_CAMERA_OV2640_ESP32_H
#define MP_CAMERA_OV2640_ESP32_H

#include "MP_DEVICE.h"
#include "camera.h"

class MP_CAMERA_OV2640_ESP32
{
public:
	MP_CAMERA_OV2640_ESP32(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4
		, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t xclk, uint8_t pclk, uint8_t vsync
		, uint8_t href, uint8_t sda, uint8_t scl, uint8_t reset);
	int init();
	void update(unsigned long currentTime);
	void printStatus();
	static const char* const* ERRORS;

	void captureImage();
    MP_IMAGE getImage();

private:
	uint8_t d0; 
	uint8_t d1; 
	uint8_t d2; 
	uint8_t d3; 
	uint8_t d4;	
	uint8_t d5; 
	uint8_t d6; 
	uint8_t d7; 
	uint8_t xclk;
	uint8_t pclk; 
	uint8_t vsync;
	uint8_t href;
	uint8_t sda;
	uint8_t scl; 
	uint8_t reset;

	MP_IMAGE image;
	esp_err_t err;
};

#endif
