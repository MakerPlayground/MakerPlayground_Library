#ifndef MP_DEVICE_H
#define MP_DEVICE_H

#include <Arduino.h>
#include "MP_DATETIME.h"
#include "MP_IMAGE.h"

#ifdef ESP32
    #include "ESP32_Polyfill.h"
#endif

#if defined(ESP32) || defined(ESP8266)
    #include "MP_RECORD.h"
#endif

// base class: MP_Device
// error msgs

#endif