#include "MP_Line_Notify.h"

#define LINE_SERVER "notify-api.line.me"
#define LINE_PORT 443
#define LINE_TIMEOUT 10000

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};
const char* const* MP_Line_Notify::ERRORS = errors_p;

MP_Line_Notify::MP_Line_Notify(String token, MP_REST* rest)
    : token(token)
    , rest(rest)
    , error(Error::OK)
{
}

int MP_Line_Notify::init()
{
    return 0;
}

void MP_Line_Notify::update(unsigned long currentTime)
{
}

void MP_Line_Notify::printStatus()
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

void MP_Line_Notify::notify(String message)
{
    sendMessage(message);
}

void MP_Line_Notify::sendMessage(String message, MP_IMAGE image)
{
    if (!rest->isConnected())
    {
        error = Error::NO_INTERNET_CONNECTION;
        return;
    }

    String boundary = "MP_Line_Notify";

    String body = "--" + boundary + "\r\n";
    body += "Content-Disposition: form-data; name=\"message\"\r\n\r\n" + message + " \r\n";
    if (image.data != NULL && image.size > 0)
    {
        body += "--" + boundary + "\r\n";
        body += "Content-Disposition: form-data; name=\"imageFile\"; filename=\"image.jpg\"\r\n"; 
        body += "Content-Type: image/jpeg\r\n\r\n";
    }
    String bodyEnd = "--" + boundary + "--\r\n";
    size_t bodyLength = body.length() + image.size + bodyEnd.length();

    String header;
    header += "POST /api/notify HTTP/1.1\r\n";
    header += "Host: notify-api.line.me\r\n";
    header += "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n";
    header += "Authorization: Bearer " + token + "\r\n";
    header += "Content-Length: " + String(bodyLength) + "\r\n";
    header += "\r\n";

    WiFiClientSecure client;
    if (!client.connect(LINE_SERVER, LINE_PORT))
    {
        error = Error::CANT_CONNECT_LINE;
        return;
    }

    client.print(header);
    client.print(body);
    if (image.data != NULL && image.size > 0)
    {
        client.write(image.data, image.size);
    }
    client.print("\r\n" + bodyEnd);

    unsigned long timeout = millis() + LINE_TIMEOUT;
    while (client.connected() && timeout > millis())
    {
        if (client.available())
        {
            String response = client.readStringUntil('\r');
            int responseCode = response.substring(9, 12).toInt();
            if (responseCode == 200)
            {
                error = Error::OK;
            }
            else if (responseCode == 401)
            {
                error = Error::INVALID_TOKEN;
            }
            else
            {
                error = Error::SERVER_ERROR;
            }
            return;
        }
        delay(10);
    }
    
    error = Error::CONNECTION_TIMEOUT;
}