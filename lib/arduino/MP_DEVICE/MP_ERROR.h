#ifndef MP_ERROR
#define MP_ERROR

#include <Arduino.h>

#define ERR_OK                  0
#define ERR_CONNECT_WIFI        1
#define ERR_CONNECT_SERVER      2
#define ERR_CLIENT_NOT_READY    3
#define ERR_CONNECT_DEVICE      4
#define ERR_CONFIG_DEVICE       5
#define ERR_INTERNAL_ERROR      6

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Can't connect to Wifi";
const char error2[] PROGMEM = "Can't connect to server";
const char error3[] PROGMEM = "Client is not ready";
const char error4[] PROGMEM = "Can't connect to device";
const char error5[] PROGMEM = "Can't configure device";
const char error6[] PROGMEM = "Internal error";
const char* const ERRORS[] PROGMEM = {ok, error1, error2, error3, error4, error5, error6};

#endif