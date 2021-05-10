#ifndef MP_CAMERA_OV2640_K210_H
#define MP_CAMERA_OV2640_K210_H

#include "MP_DEVICE.h"
#include <Sipeed_OV2640.h>

#define BUFFER_SIZE 153600 // 320*240*2

class MP_CAMERA_OV2640_K210
{
public:
	MP_CAMERA_OV2640_K210();
	int init();
	void update(unsigned long currentTime);
	void printStatus();

    MP_IMAGE getImage();

private:
	MP_IMAGE image;

	Sipeed_OV2640 camera;
	uint8_t buffer[BUFFER_SIZE];
};

#endif
