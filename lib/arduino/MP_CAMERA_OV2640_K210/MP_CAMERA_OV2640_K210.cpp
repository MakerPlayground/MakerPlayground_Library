#include "MP_CAMERA_OV2640_K210.h"

MP_CAMERA_OV2640_K210::MP_CAMERA_OV2640_K210()
    : camera(FRAMESIZE_QVGA, PIXFORMAT_RGB565)
{
}

int MP_CAMERA_OV2640_K210::init()
{
	if (!camera.begin())
	    return MP_ERR_CONNECT_DEVICE;
    camera.run(true);
    image.width = camera.width();
    image.height = camera.height();
    image.format = MP_IMAGE_FORMAT_RGB565;
    return MP_ERR_OK;
}

void MP_CAMERA_OV2640_K210::update(unsigned long current_time) 
{
    if (camera.isFrameReady())
    {
        camera.retrieveFrame();
        memcpy (buffer, (uint8_t*) camera.getRGB565(), BUFFER_SIZE);
        image.data = buffer;
        image.size = BUFFER_SIZE;
        image.id += 1;
        camera.startSnapshot();
    }
}

void MP_CAMERA_OV2640_K210::printStatus() 
{
}

MP_IMAGE MP_CAMERA_OV2640_K210::getImage()
{	
	return image;
}



