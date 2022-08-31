#ifndef MP_LINE_NOTIFY_WIOTERMINAL_H
#define MP_LINE_NOTIFY_WIOTERMINAL_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include "MP_DEVICE.h"
#include "MP_REST.h"

class MP_Line_Notify_Wioterminal
{
public:
    MP_Line_Notify_Wioterminal(String token, MP_REST* rest);
    int init();
	void update(unsigned long currentTime);
	void printStatus();

    void notify(String message);
    void sendMessage(String message, MP_IMAGE image = MP_IMAGE());

    enum class Error
    {
        OK,
        NO_INTERNET_CONNECTION,
        CANT_CONNECT_LINE,
        SERVER_ERROR,
        INVALID_TOKEN,
        CONNECTION_TIMEOUT
    };

private:
    WiFiClientSecure client;
    String token;
    MP_REST* rest;
    Error error;
};

#endif