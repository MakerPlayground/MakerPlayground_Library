/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial
#define BAUDRATE 115200
#define SEND_GAP 100    // in ms (100 mean we send 10 times / sec)
//#define CONNECTION_RETRY_GAP 1000

#include "MP_BLYNK_K210_ESP8285.h"
#include <BlynkSimpleShieldEsp8266.h>

double MP_BLYNK_K210_ESP8285::value[8];
uint8_t MP_BLYNK_K210_ESP8285::valueChanged;

MP_BLYNK_K210_ESP8285::MP_BLYNK_K210_ESP8285(char* auth, char* ssid, char* pass)
    : wifi(&Serial1)
    , auth(auth)
    , ssid(ssid)
    , pass(pass)
    , lastSendMillis(0)
{
    for (uint8_t i=0; i<8; i++)
    {
        MP_BLYNK_K210_ESP8285::value[i] = 0;
    }
}

int MP_BLYNK_K210_ESP8285::init() 
{
    Serial1.begin(BAUDRATE, 13, 14);
    delay(100);

//    // this version may be used to connect to blynk without blocking the whole program
//    Blynk.config(wifi, auth, BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT);
//
//    if (!connectWifi()) {
//        return MP_ERR_CONNECT_WIFI;
//    }
//
//    while (!Blynk.connect()) {
//    }

    Blynk.begin(auth, wifi, ssid, pass);
    return MP_ERR_OK;
}

//bool MP_BLYNK_K210_ESP8285::connectWifi()
//{
//    int retry = 5;
//    while (!Blynk.connectWiFi(this->ssid, this->pass)) {
//        delay(CONNECTION_RETRY_GAP);
//        if (retry == 0) {
//            return false;
//        }
//        retry--;
//    }
//    return true;
//}
//
//bool MP_BLYNK_K210_ESP8285::testPing()
//{
//    int pingRetry = 5;
//    while (pingRetry > 0) {
//        // test connection
//        if (wifi.setPing("4.2.2.2")) {
//            return true;
//        }
//        pingRetry--;
//        delay(CONNECTION_RETRY_GAP);
//    }
//    return false;
//}

void MP_BLYNK_K210_ESP8285::update(unsigned long time) 
{
    Blynk.run();
    // push value waited to be push to blynk server
    if (time - lastSendMillis > SEND_GAP) 
    {
        for (uint8_t i=0; i<8; i++)
        {
            if (MP_BLYNK_K210_ESP8285::valueChanged & (1 << i)) 
            {
                Blynk.virtualWrite(i, MP_BLYNK_K210_ESP8285::value[i]);
                MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << i);
            }
        }
        lastSendMillis = time;
    }
}

void MP_BLYNK_K210_ESP8285::printStatus()
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

bool MP_BLYNK_K210_ESP8285::isReady()
{
    return Blynk.connected();
}

int MP_BLYNK_K210_ESP8285::readVirtualPin(uint8_t pin) 
{
    return MP_BLYNK_K210_ESP8285::value[pin];
}

void MP_BLYNK_K210_ESP8285::writeVirtualPin(uint8_t pin, double value)
{
    MP_BLYNK_K210_ESP8285::value[pin] = value;
    MP_BLYNK_K210_ESP8285::valueChanged |= (1 << pin);
}

void MP_BLYNK_K210_ESP8285::writeVirtualPin(uint8_t pin, int val1, double val2, double val3, char* val4)
{
    Blynk.virtualWrite(pin, val1, val2, val3, val4);
}

void MP_BLYNK_K210_ESP8285::writeVirtualPin(uint8_t pin, char* val1)
{
    Blynk.virtualWrite(pin, val1);
}

void MP_BLYNK_K210_ESP8285::notify(const char* msg) {
    Blynk.notify(msg);
}

bool MP_BLYNK_K210_ESP8285::checkVirtualPinValue(uint8_t pin, int value)
{
    return MP_BLYNK_K210_ESP8285::value[pin] == value;
}

int MP_BLYNK_K210_ESP8285::getVirtualPin0()
{
    return this->readVirtualPin(0);
}

int MP_BLYNK_K210_ESP8285::getVirtualPin1()
{
    return this->readVirtualPin(1);
}

int MP_BLYNK_K210_ESP8285::getVirtualPin2()
{
    return this->readVirtualPin(2);
}

int MP_BLYNK_K210_ESP8285::getVirtualPin3()
{
    return this->readVirtualPin(3);
}

int MP_BLYNK_K210_ESP8285::getVirtualPin4()
{
    return this->readVirtualPin(4);
}

int MP_BLYNK_K210_ESP8285::getVirtualPin5()
{
    return this->readVirtualPin(5);
}

int MP_BLYNK_K210_ESP8285::getVirtualPin6()
{
    return this->readVirtualPin(6);
}

int MP_BLYNK_K210_ESP8285::getVirtualPin7()
{
    return this->readVirtualPin(7);
}

BLYNK_READ(V0) 
{
    Blynk.virtualWrite(0, MP_BLYNK_K210_ESP8285::value[0]);
    MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << 0);
}

BLYNK_READ(V1) 
{
    Blynk.virtualWrite(1, MP_BLYNK_K210_ESP8285::value[1]);
    MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << 1);
}

BLYNK_READ(V2) 
{
    Blynk.virtualWrite(2, MP_BLYNK_K210_ESP8285::value[2]);
    MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << 2);
}

BLYNK_READ(V3) 
{
    Blynk.virtualWrite(3, MP_BLYNK_K210_ESP8285::value[3]);
    MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << 3);
}

BLYNK_READ(V4) 
{
    Blynk.virtualWrite(4, MP_BLYNK_K210_ESP8285::value[4]);
    MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << 4);
}

BLYNK_READ(V5) 
{
    Blynk.virtualWrite(5, MP_BLYNK_K210_ESP8285::value[5]);
    MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << 5);
}

BLYNK_READ(V6) 
{
    Blynk.virtualWrite(6, MP_BLYNK_K210_ESP8285::value[6]);
    MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << 6);
}

BLYNK_READ(V7) 
{
    Blynk.virtualWrite(7, MP_BLYNK_K210_ESP8285::value[7]);
    MP_BLYNK_K210_ESP8285::valueChanged &= ~(1 << 7);
}

BLYNK_WRITE(V0) 
{
    MP_BLYNK_K210_ESP8285::value[0] = param.asInt();
}

BLYNK_WRITE(V1) 
{
    MP_BLYNK_K210_ESP8285::value[1] = param.asInt();
}

BLYNK_WRITE(V2) 
{
    MP_BLYNK_K210_ESP8285::value[2] = param.asInt();
}

BLYNK_WRITE(V3) 
{
    MP_BLYNK_K210_ESP8285::value[3] = param.asInt();
}

BLYNK_WRITE(V4) 
{
    MP_BLYNK_K210_ESP8285::value[4] = param.asInt();
}

BLYNK_WRITE(V5) 
{
    MP_BLYNK_K210_ESP8285::value[5] = param.asInt();
}

BLYNK_WRITE(V6) 
{
    MP_BLYNK_K210_ESP8285::value[6] = param.asInt();
}

BLYNK_WRITE(V7) 
{
    MP_BLYNK_K210_ESP8285::value[7] = param.asInt();
}