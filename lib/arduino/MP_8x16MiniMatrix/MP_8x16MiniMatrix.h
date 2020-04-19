#ifndef MP_8x16MiniMatrix_H
#define MP_8x16MiniMatrix_H

#include "MP_DEVICE.h"
#include <Wire.h>
#include "SPI.h"
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#define MODE_CLEAR    ((uint8_t) 0)
#define MODE_TEXT     ((uint8_t) 1)
#define MODE_BITMAP   ((uint8_t) 2)

class MP_8x16MiniMatrix
{
public:
	MP_8x16MiniMatrix();
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
    void showText(const char* text, uint8_t text_size, int rotation);
	void clear();

private:
    Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();
	
    String valueToShow;
    uint8_t showMode;
    int8_t textScrollStart;
    int8_t textScrollStop;
    int8_t textScrollCurrent;

    unsigned long last_update;
};

#endif
