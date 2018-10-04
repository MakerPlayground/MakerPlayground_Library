#if defined(GROVE_ARDUINO)

#define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
#define SEND_GAP 100    // in ms (100 mean we send 10 times / sec)

#include "MP_BLYNK_SERIAL_WIFI.h"
#include <BlynkSimpleShieldEsp8266.h>

MP_BLYNK_SERIAL_WIFI* MP_BLYNK_SERIAL_WIFI::instance = 0; // NULL
double MP_BLYNK_SERIAL_WIFI::value[8];
uint8_t MP_BLYNK_SERIAL_WIFI::valueChanged;

void MP_BLYNK_SERIAL_WIFI::setup(char auth[], char ssid[], char pass[]) {
    instance = new MP_BLYNK_SERIAL_WIFI(auth, ssid, pass);
}

MP_BLYNK_SERIAL_WIFI* MP_BLYNK_SERIAL_WIFI::getInstance() {
    return instance;
}

MP_BLYNK_SERIAL_WIFI::MP_BLYNK_SERIAL_WIFI(uint8_t rx, uint8_t tx, char* auth, char* ssid, char* pass)
    : espSerial(SoftwareSerial(rx, tx))
    , wifi(&espSerial)
    , auth(auth)
    , ssid(ssid)
    , pass(pass)
    , lastSendMillis(0)
{
    for (uint8_t i=0; i<8; i++)
    {
        MP_BLYNK_SERIAL_WIFI::value[i] = 0;
    }
}

void MP_BLYNK_SERIAL_WIFI::init() 
{
    this->espSerial.begin(ESP8266_BAUD);
    delay(10);
    Blynk.begin(this->auth, this->wifi, this->ssid, this->pass);
}

void MP_BLYNK_SERIAL_WIFI::update(unsigned long time) 
{
    Blynk.run();
    // push value waited to be push to blynk server
    if (time - lastSendMillis > SEND_GAP) 
    {
        for (uint8_t i=0; i<8; i++)
        {
            if (MP_BLYNK_SERIAL_WIFI::valueChanged & (1 << i)) 
            {
                Blynk.virtualWrite(i, MP_BLYNK_SERIAL_WIFI::value[i]);
                MP_BLYNK_SERIAL_WIFI::valueChanged &= ~(1 << i);
            }
        }
        lastSendMillis = time;
    }
}

int MP_BLYNK_SERIAL_WIFI::readVirtualPin(uint8_t pin) 
{
    return MP_BLYNK_SERIAL_WIFI::value[pin];
}

void MP_BLYNK_SERIAL_WIFI::writeVirtualPin(char pin[], double value)
{
    MP_BLYNK_SERIAL_WIFI::value[pin[0] - '0'] = value;
    MP_BLYNK_SERIAL_WIFI::valueChanged |= (1 << (pin[0] - '0'));
}

bool MP_BLYNK_SERIAL_WIFI::checkVirtualPinValue(char pin[], int value)
{
    return MP_BLYNK_SERIAL_WIFI::value[pin[0] - '0'] == value;
}

int MP_BLYNK_SERIAL_WIFI::getVirtualPin0()
{
    return this->readVirtualPin(0);
}

int MP_BLYNK_SERIAL_WIFI::getVirtualPin1()
{
    return this->readVirtualPin(1);
}

int MP_BLYNK_SERIAL_WIFI::getVirtualPin2()
{
    return this->readVirtualPin(2);
}

int MP_BLYNK_SERIAL_WIFI::getVirtualPin3()
{
    return this->readVirtualPin(3);
}

int MP_BLYNK_SERIAL_WIFI::getVirtualPin4()
{
    return this->readVirtualPin(4);
}

int MP_BLYNK_SERIAL_WIFI::getVirtualPin5()
{
    return this->readVirtualPin(5);
}

int MP_BLYNK_SERIAL_WIFI::getVirtualPin6()
{
    return this->readVirtualPin(6);
}

int MP_BLYNK_SERIAL_WIFI::getVirtualPin7()
{
    return this->readVirtualPin(7);
}

BLYNK_READ(V0) 
{
    Blynk.virtualWrite(0, MP_BLYNK_SERIAL_WIFI::value[0]);
    MP_BLYNK_SERIAL_WIFI::valueChanged &= ~_BV(0);
}

BLYNK_READ(V1) 
{
    Blynk.virtualWrite(1, MP_BLYNK_SERIAL_WIFI::value[1]);
    MP_BLYNK_SERIAL_WIFI::valueChanged &= ~_BV(1);
}

BLYNK_READ(V2) 
{
    Blynk.virtualWrite(2, MP_BLYNK_SERIAL_WIFI::value[2]);
    MP_BLYNK_SERIAL_WIFI::valueChanged &= ~_BV(2);
}

BLYNK_READ(V3) 
{
    Blynk.virtualWrite(3, MP_BLYNK_SERIAL_WIFI::value[3]);
    MP_BLYNK_SERIAL_WIFI::valueChanged &= ~_BV(3);
}

BLYNK_READ(V4) 
{
    Blynk.virtualWrite(4, MP_BLYNK_SERIAL_WIFI::value[4]);
    MP_BLYNK_SERIAL_WIFI::valueChanged &= ~_BV(4);
}

BLYNK_READ(V5) 
{
    Blynk.virtualWrite(5, MP_BLYNK_SERIAL_WIFI::value[5]);
    MP_BLYNK_SERIAL_WIFI::valueChanged &= ~_BV(5);
}

BLYNK_READ(V6) 
{
    Blynk.virtualWrite(6, MP_BLYNK_SERIAL_WIFI::value[6]);
    MP_BLYNK_SERIAL_WIFI::valueChanged &= ~_BV(6);
}

BLYNK_READ(V7) 
{
    Blynk.virtualWrite(7, MP_BLYNK_SERIAL_WIFI::value[7]);
    MP_BLYNK_SERIAL_WIFI::valueChanged &= ~_BV(7);
}

BLYNK_WRITE(V0) 
{
    MP_BLYNK_SERIAL_WIFI::value[0] = param.asInt();
}

BLYNK_WRITE(V1) 
{
    MP_BLYNK_SERIAL_WIFI::value[1] = param.asInt();
}

BLYNK_WRITE(V2) 
{
    MP_BLYNK_SERIAL_WIFI::value[2] = param.asInt();
}

BLYNK_WRITE(V3) 
{
    MP_BLYNK_SERIAL_WIFI::value[3] = param.asInt();
}

BLYNK_WRITE(V4) 
{
    MP_BLYNK_SERIAL_WIFI::value[4] = param.asInt();
}

BLYNK_WRITE(V5) 
{
    MP_BLYNK_SERIAL_WIFI::value[5] = param.asInt();
}

BLYNK_WRITE(V6) 
{
    MP_BLYNK_SERIAL_WIFI::value[6] = param.asInt();
}

BLYNK_WRITE(V7) 
{
    MP_BLYNK_SERIAL_WIFI::value[7] = param.asInt();
}

#endif