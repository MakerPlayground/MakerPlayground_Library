/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
#define SEND_GAP 100    // in ms (100 mean we send 10 times / sec)

#include "MP_BLYNK_NODEMCU.h"

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Can't connect to access point";
const char error2[] PROGMEM = "Can't connect to Blynk Server";
const char* const errors_p[] PROGMEM = {ok, error1, error2};

const char* const* MP_BLYNK::ERRORS = errors_p;

double MP_BLYNK_NODEMCU::value[8];
uint8_t MP_BLYNK_NODEMCU::valueChanged;

MP_BLYNK_NODEMCU::MP_BLYNK_NODEMCU(char* auth, char* ssid, char* pass)
    : auth(auth)
    , ssid(ssid)
    , pass(pass)
    , lastSendMillis(0)
{
    for (uint8_t i=0; i<8; i++)
    {
        MP_BLYNK_NODEMCU::value[i] = 0;
    }
}

int MP_BLYNK_NODEMCU::init() 
{
    Blynk.config(auth, BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT);
    
    if (!connectWifi()) {
        return 1;
    }

    if (!Blynk.connect()) {
        return 2;
    }
    
    return 0;
}

bool MP_BLYNK_NODEMCU::connectWifi()
{
    int retry = 5;
    while (WiFi.status() != WL_CONNECTED) {
        Blynk.connectWiFi(this->ssid, this->pass);
        delay(1);
        if (retry == 0) {
            return false;
        }
        retry--;
    }
    return true;
}

void MP_BLYNK_NODEMCU::update(unsigned long time) 
{
    Blynk.run();
    // push value waited to be push to blynk server
    if (time - lastSendMillis > SEND_GAP) 
    {
        for (uint8_t i=0; i<8; i++)
        {
            if (MP_BLYNK_NODEMCU::valueChanged & (1 << i)) 
            {
                Blynk.virtualWrite(i, MP_BLYNK_NODEMCU::value[i]);
                MP_BLYNK_NODEMCU::valueChanged &= ~(1 << i);
            }
        }
        lastSendMillis = time;
    }
}

void MP_BLYNK_NODEMCU::printStatus()
{
    Serial.print(F("Current virtual pin status = "));
    Serial.print(getVirtualPin0());
    Serial.print(F(" "));
    Serial.print(getVirtualPin1());
    Serial.print(F(" "));
    Serial.print(getVirtualPin2());
    Serial.print(F(" "));
    Serial.print(getVirtualPin3());
    Serial.print(F(" "));
    Serial.print(getVirtualPin4());
    Serial.print(F(" "));
    Serial.print(getVirtualPin5());
    Serial.print(F(" "));
    Serial.print(getVirtualPin6());
    Serial.print(F(" "));
    Serial.print(getVirtualPin7());
    Serial.println();
}

bool MP_BLYNK_NODEMCU::isReady()
{
    return WiFi.status() == WL_CONNECTED;
}

int MP_BLYNK_NODEMCU::readVirtualPin(uint8_t pin) 
{
    return MP_BLYNK_NODEMCU::value[pin];
}

void MP_BLYNK_NODEMCU::writeVirtualPin(uint8_t pin, double value)
{
    MP_BLYNK_NODEMCU::value[pin] = value;
    MP_BLYNK_NODEMCU::valueChanged |= (1 << pin);
}

bool MP_BLYNK_NODEMCU::checkVirtualPinValue(uint8_t pin, int value)
{
    return MP_BLYNK_NODEMCU::value[pin] == value;
}

int MP_BLYNK_NODEMCU::getVirtualPin0()
{
    return this->readVirtualPin(0);
}

int MP_BLYNK_NODEMCU::getVirtualPin1()
{
    return this->readVirtualPin(1);
}

int MP_BLYNK_NODEMCU::getVirtualPin2()
{
    return this->readVirtualPin(2);
}

int MP_BLYNK_NODEMCU::getVirtualPin3()
{
    return this->readVirtualPin(3);
}

int MP_BLYNK_NODEMCU::getVirtualPin4()
{
    return this->readVirtualPin(4);
}

int MP_BLYNK_NODEMCU::getVirtualPin5()
{
    return this->readVirtualPin(5);
}

int MP_BLYNK_NODEMCU::getVirtualPin6()
{
    return this->readVirtualPin(6);
}

int MP_BLYNK_NODEMCU::getVirtualPin7()
{
    return this->readVirtualPin(7);
}

BLYNK_READ(V0) 
{
    Blynk.virtualWrite(0, MP_BLYNK_NODEMCU::value[0]);
    MP_BLYNK_NODEMCU::valueChanged &= ~_BV(0);
}

BLYNK_READ(V1) 
{
    Blynk.virtualWrite(1, MP_BLYNK_NODEMCU::value[1]);
    MP_BLYNK_NODEMCU::valueChanged &= ~_BV(1);
}

BLYNK_READ(V2) 
{
    Blynk.virtualWrite(2, MP_BLYNK_NODEMCU::value[2]);
    MP_BLYNK_NODEMCU::valueChanged &= ~_BV(2);
}

BLYNK_READ(V3) 
{
    Blynk.virtualWrite(3, MP_BLYNK_NODEMCU::value[3]);
    MP_BLYNK_NODEMCU::valueChanged &= ~_BV(3);
}

BLYNK_READ(V4) 
{
    Blynk.virtualWrite(4, MP_BLYNK_NODEMCU::value[4]);
    MP_BLYNK_NODEMCU::valueChanged &= ~_BV(4);
}

BLYNK_READ(V5) 
{
    Blynk.virtualWrite(5, MP_BLYNK_NODEMCU::value[5]);
    MP_BLYNK_NODEMCU::valueChanged &= ~_BV(5);
}

BLYNK_READ(V6) 
{
    Blynk.virtualWrite(6, MP_BLYNK_NODEMCU::value[6]);
    MP_BLYNK_NODEMCU::valueChanged &= ~_BV(6);
}

BLYNK_READ(V7) 
{
    Blynk.virtualWrite(7, MP_BLYNK_NODEMCU::value[7]);
    MP_BLYNK_NODEMCU::valueChanged &= ~_BV(7);
}

BLYNK_WRITE(V0) 
{
    MP_BLYNK_NODEMCU::value[0] = param.asInt();
}

BLYNK_WRITE(V1) 
{
    MP_BLYNK_NODEMCU::value[1] = param.asInt();
}

BLYNK_WRITE(V2) 
{
    MP_BLYNK_NODEMCU::value[2] = param.asInt();
}

BLYNK_WRITE(V3) 
{
    MP_BLYNK_NODEMCU::value[3] = param.asInt();
}

BLYNK_WRITE(V4) 
{
    MP_BLYNK_NODEMCU::value[4] = param.asInt();
}

BLYNK_WRITE(V5) 
{
    MP_BLYNK_NODEMCU::value[5] = param.asInt();
}

BLYNK_WRITE(V6) 
{
    MP_BLYNK_NODEMCU::value[6] = param.asInt();
}

BLYNK_WRITE(V7) 
{
    MP_BLYNK_NODEMCU::value[7] = param.asInt();
}