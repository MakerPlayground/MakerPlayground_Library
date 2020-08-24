#include "MP_CAMERA_OV2640_ESP32.h"

MP_CAMERA_OV2640_ESP32::MP_CAMERA_OV2640_ESP32(uint8_t d0, uint8_t d1, uint8_t d2
	, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t xclk, uint8_t pclk
	, uint8_t vsync, uint8_t href, uint8_t sda, uint8_t scl, uint8_t reset)
	: d0(d0), d1(d1), d2(d2), d3(d3), d4(d4), d5(d5), d6(d6), d7(d7), xclk(xclk)
	, pclk(pclk), vsync(vsync), href(href), sda(sda), scl(scl), reset(reset), err(ESP_OK)
{
}

int MP_CAMERA_OV2640_ESP32::init()
{
	camera_config_t config; 
	config.ledc_channel = LEDC_CHANNEL_0;	// overlap with ledc channel 0, 1, 8, 9 see esp32-hal-ledc.c
	config.ledc_timer = LEDC_TIMER_0;
	config.pin_d0 = d0;
	config.pin_d1 = d1;
	config.pin_d2 = d2;
	config.pin_d3 = d3;
	config.pin_d4 = d4;
	config.pin_d5 = d5;
	config.pin_d6 = d6;
	config.pin_d7 = d7;
	config.pin_xclk = xclk;
	config.pin_pclk = pclk;
	config.pin_vsync = vsync;
	config.pin_href = href;
	config.pin_sscb_sda = sda;
	config.pin_sscb_scl = scl;
	config.pin_reset = reset;
	config.xclk_freq_hz = 10000000;
	config.pixel_format = CAMERA_PF_JPEG;
	config.frame_size = CAMERA_FS_QVGA;
	config.jpeg_quality = 15;
	config.mirror = 0;
	config.vflip = 0;
	config.whitebal = 1;

	err = camera_init(&config);
    if (err != ESP_OK)
        return MP_ERR_CONNECT_DEVICE;

    return MP_ERR_OK;
}

void MP_CAMERA_OV2640_ESP32::update(unsigned long current_time) 
{
	err = camera_run();
	if (err == ESP_OK) 
	{
		image.data = camera_get_fb();
		image.size = camera_get_data_size() - 1;
		image.id += 1;
	}
}

void MP_CAMERA_OV2640_ESP32::printStatus() 
{
	if (err == ESP_OK)
	{
		Serial.println(F("camera is working"));
	}
	else
	{
		Serial.println(F("found error while capturing image"));
	}
}

MP_IMAGE MP_CAMERA_OV2640_ESP32::getImage()
{	
	return image;
}



