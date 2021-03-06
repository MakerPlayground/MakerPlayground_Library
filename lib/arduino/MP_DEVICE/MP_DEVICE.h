#ifndef MP_DEVICE_H
#define MP_DEVICE_H

#include "MP_DATETIME.h"
#include "MP_IMAGE.h"
#include "MP_ERROR.h"
#include "MP_INTERACTIVE.h"

#ifdef ESP32
    #include "ESP32_Polyfill.h"
#endif

#if defined(ESP32) || defined(ESP8266)
    #include "MP_RECORD.h"
#endif

// base class: MP_Device
// error msgs

#endif