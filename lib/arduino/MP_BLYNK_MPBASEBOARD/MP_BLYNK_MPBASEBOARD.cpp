
#define UPDATE_INTERVAL 500

#include "MP_BLYNK_MPBASEBOARD.h"

MP_BLYNK_MPBASEBOARD::MP_BLYNK_MPBASEBOARD(char* auth, char* ssid, char* pass)
    : auth(auth)
    , ssid(ssid)
    , pass(pass)
    , lastSendMillis(0)
{
    for (uint8_t i=0; i<8; i++)
    {
        value[i] = 0;
    }
}

bool MP_BLYNK_MPBASEBOARD::checkResponse()
{
    return Serial1.readStringUntil('\n').equals("OK\r");
}

bool MP_BLYNK_MPBASEBOARD::isReady()
{
    return true;    // TODO: we shouldn't always return true
}

int MP_BLYNK_MPBASEBOARD::init() 
{
    Serial1.begin(115200);
    Serial1.setTimeout(5000);
    delay(10);

    // connect to wifi and wait for response
    Serial1.print(F("W,"));
    Serial1.print(ssid);
    Serial1.print(F(","));
    Serial1.println(pass);
    if (!checkResponse())
    {
        return MP_ERR_CONNECT_WIFI;
    }

    // connect to blynk
    Serial1.print(F("B,"));
    Serial1.println(auth);
    if (!checkResponse())
    {
        return MP_ERR_CONNECT_SERVER;
    }

    return MP_ERR_OK;
}

void MP_BLYNK_MPBASEBOARD::printStatus()
{
    Serial.print(F("Current virtual pin status = "));
    Serial.print(String(value[0]));
    for (uint8_t i=1; i<8; i++)
    {
        Serial.print(F(","));
        Serial.print(String(value[i]));
    }
}

void MP_BLYNK_MPBASEBOARD::update(unsigned long time) 
{
    if (time - lastSendMillis > UPDATE_INTERVAL)
    {
        for (uint8_t i=0; i<8; i++)
        {
            Serial1.print(F("R,"));
            Serial1.println((char) (i + '0'));
            value[i] = Serial1.parseInt();
            checkResponse();    // TODO: we shoudn't suspress error
        }
        lastSendMillis = time;
    }
}

int MP_BLYNK_MPBASEBOARD::readVirtualPin(uint8_t pin) 
{
    return value[pin];
}

void MP_BLYNK_MPBASEBOARD::writeVirtualPin(uint8_t pin, double value)
{
    Serial1.print(F("V,"));
    Serial1.print((char) (pin + '0'));
    Serial1.print(F(","));
    Serial1.println(String(value));
    checkResponse();
}

void MP_BLYNK_MPBASEBOARD::writeVirtualPin(uint8_t pin, int val1, double val2, double val3, char* val4)
{
    Serial1.print(F("C,"));
    Serial1.print(((char) pin + '0'));
    Serial1.print(F(","));
    Serial1.print(String(val1));
    Serial1.print(F(","));
    Serial1.print(String(val2));
    Serial1.print(F(","));
    Serial1.print(String(val3));
    Serial1.print(F(","));
    Serial1.println(val4);
    checkResponse();
}

void MP_BLYNK_MPBASEBOARD::writeVirtualPin(uint8_t pin, char* val1)
{
    Serial1.print(F("C,"));
    Serial1.print(((char) pin + '0'));
    Serial1.print(F(","));
    Serial1.println(val1);
    checkResponse();
}

void MP_BLYNK_MPBASEBOARD::notify(const char* msg) {
    Serial1.print(F("A,"));
    Serial1.println(msg);
    checkResponse();
}

bool MP_BLYNK_MPBASEBOARD::checkVirtualPinValue(uint8_t pin, int v)
{
    return ((int) value[pin]) == v;
}

int MP_BLYNK_MPBASEBOARD::getVirtualPin0()
{
    return this->readVirtualPin(0);
}

int MP_BLYNK_MPBASEBOARD::getVirtualPin1()
{
    return this->readVirtualPin(1);
}

int MP_BLYNK_MPBASEBOARD::getVirtualPin2()
{
    return this->readVirtualPin(2);
}

int MP_BLYNK_MPBASEBOARD::getVirtualPin3()
{
    return this->readVirtualPin(3);
}

int MP_BLYNK_MPBASEBOARD::getVirtualPin4()
{
    return this->readVirtualPin(4);
}

int MP_BLYNK_MPBASEBOARD::getVirtualPin5()
{
    return this->readVirtualPin(5);
}

int MP_BLYNK_MPBASEBOARD::getVirtualPin6()
{
    return this->readVirtualPin(6);
}

int MP_BLYNK_MPBASEBOARD::getVirtualPin7()
{
    return this->readVirtualPin(7);
}