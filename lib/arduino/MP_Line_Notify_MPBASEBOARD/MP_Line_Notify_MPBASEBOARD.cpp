#include "MP_Line_Notify_MPBASEBOARD.h"

MP_Line_Notify_MPBASEBOARD::MP_Line_Notify_MPBASEBOARD(String token, MP_REST* rest)
    : token(token)
    , error(Error::OK)
{
}

int MP_Line_Notify_MPBASEBOARD::init()
{
    Serial1.print(F("L\r"));
    Serial1.println(token);
    if (!checkResponse())
    {
        return MP_ERR_CONNECT_SERVER;
    }
    return MP_ERR_OK;
}

void MP_Line_Notify_MPBASEBOARD::update(unsigned long currentTime)
{
}

void MP_Line_Notify_MPBASEBOARD::printStatus()
{
    switch (error)
    {
        case Error::OK:
            Serial.println("OK");
            break;
        case Error::NO_INTERNET_CONNECTION:
            Serial.println(F("Wifi is not connected"));
            break;
        case Error::CANT_CONNECT_LINE:
            Serial.println(F("Can't connect to LINE Notify services endpoint"));
            break;
        case Error::SERVER_ERROR:
            Serial.println(F("Got error reponse code from the server"));
            break;
        case Error::INVALID_TOKEN:
            Serial.println(F("Invalid LINE Notify token"));
            break;
        case Error::CONNECTION_TIMEOUT:
            Serial.println(F("Connection timeout"));
            break;
    }
}

void MP_Line_Notify_MPBASEBOARD::notify(String message)
{
    sendMessage(message);
}

bool MP_Line_Notify_MPBASEBOARD::checkResponse()
{
    return Serial1.readStringUntil('\n').equals("OK\r");
}

void MP_Line_Notify_MPBASEBOARD::sendMessage(String message, MP_IMAGE image)
{
    Serial1.print(F("N\r"));
    Serial1.println(message);
    if (!checkResponse())
    {
        error = Error::CANT_CONNECT_LINE;
    }
}