#ifndef MP_IMAGE_H
#define MP_IMAGE_H

#include "Arduino.h"

struct MP_IMAGE {
    unsigned int id = 0;    // auto increment id used to cache result of image processing operation
    uint8_t* data = NULL;   // pointer to the image data (CAUTION: the memory location may be resused)
    unsigned int size = 0;  // size of the image data in byte
};

#endif