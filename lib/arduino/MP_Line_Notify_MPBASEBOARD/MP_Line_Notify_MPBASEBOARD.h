#ifndef MP_LINE_NOTIFY_MPBASEBOARD_H
#define MP_LINE_NOTIFY_MPBASEBOARD_H

#include "MP_DEVICE.h"
#include "MP_REST.h"

class MP_Line_Notify_MPBASEBOARD
{
public:
    MP_Line_Notify_MPBASEBOARD(String token, MP_REST* rest);
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
    bool checkResponse();

    String token;
    Error error;
};

#endif