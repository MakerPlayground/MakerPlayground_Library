#include "MP_Line_Notify.h"

#define LINE_SERVER "notify-api.line.me"
#define LINE_PORT 443
#define LINE_TIMEOUT 10000

const char* rootCA = \
"-----BEGIN CERTIFICATE-----\n"
"MIIETjCCAzagAwIBAgINAe5fIh38YjvUMzqFVzANBgkqhkiG9w0BAQsFADBMMSAw\n"
"HgYDVQQLExdHbG9iYWxTaWduIFJvb3QgQ0EgLSBSMzETMBEGA1UEChMKR2xvYmFs\n"
"U2lnbjETMBEGA1UEAxMKR2xvYmFsU2lnbjAeFw0xODExMjEwMDAwMDBaFw0yODEx\n"
"MjEwMDAwMDBaMFAxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52\n"
"LXNhMSYwJAYDVQQDEx1HbG9iYWxTaWduIFJTQSBPViBTU0wgQ0EgMjAxODCCASIw\n"
"DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKdaydUMGCEAI9WXD+uu3Vxoa2uP\n"
"UGATeoHLl+6OimGUSyZ59gSnKvuk2la77qCk8HuKf1UfR5NhDW5xUTolJAgvjOH3\n"
"idaSz6+zpz8w7bXfIa7+9UQX/dhj2S/TgVprX9NHsKzyqzskeU8fxy7quRU6fBhM\n"
"abO1IFkJXinDY+YuRluqlJBJDrnw9UqhCS98NE3QvADFBlV5Bs6i0BDxSEPouVq1\n"
"lVW9MdIbPYa+oewNEtssmSStR8JvA+Z6cLVwzM0nLKWMjsIYPJLJLnNvBhBWk0Cq\n"
"o8VS++XFBdZpaFwGue5RieGKDkFNm5KQConpFmvv73W+eka440eKHRwup08CAwEA\n"
"AaOCASkwggElMA4GA1UdDwEB/wQEAwIBhjASBgNVHRMBAf8ECDAGAQH/AgEAMB0G\n"
"A1UdDgQWBBT473/yzXhnqN5vjySNiPGHAwKz6zAfBgNVHSMEGDAWgBSP8Et/qC5F\n"
"JK5NUPpjmove4t0bvDA+BggrBgEFBQcBAQQyMDAwLgYIKwYBBQUHMAGGImh0dHA6\n"
"Ly9vY3NwMi5nbG9iYWxzaWduLmNvbS9yb290cjMwNgYDVR0fBC8wLTAroCmgJ4Yl\n"
"aHR0cDovL2NybC5nbG9iYWxzaWduLmNvbS9yb290LXIzLmNybDBHBgNVHSAEQDA+\n"
"MDwGBFUdIAAwNDAyBggrBgEFBQcCARYmaHR0cHM6Ly93d3cuZ2xvYmFsc2lnbi5j\n"
"b20vcmVwb3NpdG9yeS8wDQYJKoZIhvcNAQELBQADggEBAJmQyC1fQorUC2bbmANz\n"
"EdSIhlIoU4r7rd/9c446ZwTbw1MUcBQJfMPg+NccmBqixD7b6QDjynCy8SIwIVbb\n"
"0615XoFYC20UgDX1b10d65pHBf9ZjQCxQNqQmJYaumxtf4z1s4DfjGRzNpZ5eWl0\n"
"6r/4ngGPoJVpjemEuunl1Ig423g7mNA2eymw0lIYkN5SQwCuaifIFJ6GlazhgDEw\n"
"fpolu4usBCOmmQDo8dIm7A9+O4orkjgTHY+GzYZSR+Y0fFukAj6KYXwidlNalFMz\n"
"hriSqHKvoflShx8xpfywgVcvzfTO3PYkz6fiNJBonf6q8amaEsybwMbDqKWwIX7e\n"
"SPY=\n"
"-----END CERTIFICATE-----\n";

MP_Line_Notify::MP_Line_Notify(String token, MP_REST* rest)
    : token(token)
    , rest(rest)
    , error(Error::OK)
{
}

int MP_Line_Notify::init()
{
    return MP_ERR_OK;
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
    client.setCACert(rootCA);
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