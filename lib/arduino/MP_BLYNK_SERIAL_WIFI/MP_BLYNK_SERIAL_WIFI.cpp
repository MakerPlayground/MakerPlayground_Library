/* Comment this out to disable prints and save space */
// #define BLYNK_PRINT Serial
#define ESP8266_BAUD 9600
#define SEND_GAP 100    // in ms (100 mean we send 10 times / sec)

#include "MP_BLYNK_SERIAL_WIFI.h"
#include <BlynkSimpleShieldEsp8266.h>

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "ESP is not response";
const char error2[] PROGMEM = "Can't connect to access point";
const char error3[] PROGMEM = "Can't connect to internet";
const char error4[] PROGMEM = "Can't connect to Blynk Server";
const char* const errors_p[] PROGMEM = {ok, error1, error2, error3, error4};

const char* const* MP_BLYNK_SERIAL_WIFI::ERRORS = errors_p;

double MP_BLYNK_SERIAL_WIFI::value[8];
uint8_t MP_BLYNK_SERIAL_WIFI::valueChanged;

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

int MP_BLYNK_SERIAL_WIFI::init() 
{
    espSerial.begin(ESP8266_BAUD);
    delay(10);

    if (espSerial.kick()) {
        return 1;
    }

    Blynk.config(wifi, auth, BLYNK_DEFAULT_DOMAIN, BLYNK_DEFAULT_PORT);
    
    if (!connectWifi()) {
        return 2;
    }

    if (!testPing()) {
        return 3;
    }

    if (!Blynk.connect()) {
        return 4;
    }
    
    return 0;
}

bool MP_BLYNK_SERIAL_WIFI::connectWifi()
{
    int retry = 5;
    while (!Blynk.connectWiFi(this->ssid, this->pass)) {
        delay(1);
        if (retry == 0) {
            return false;
        }
        retry--;
    }
    return true;
}

bool MP_BLYNK_SERIAL_WIFI::testPing()
{
    int pingRetry = 5;
    while (pingRetry > 0) {
        // test connection
        if (wifi.setPing("4.2.2.2")) {
            return true;
        }
        pingRetry--;
        delay(PING_GAP);
    }
    return false;
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

void MP_BLYNK_SERIAL_WIFI::printStatus()
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

bool MP_BLYNK_SERIAL_WIFI::isReady()
{
    return testPing();
}

int MP_BLYNK_SERIAL_WIFI::readVirtualPin(uint8_t pin) 
{
    return MP_BLYNK_SERIAL_WIFI::value[pin];
}

void MP_BLYNK_SERIAL_WIFI::writeVirtualPin(uint8_t pin, double value)
{
    MP_BLYNK_SERIAL_WIFI::value[pin] = value;
    MP_BLYNK_SERIAL_WIFI::valueChanged |= (1 << pin);
}

void MP_BLYNK_SERIAL_WIFI::writeVirtualPin(uint8_t pin, int val1, double val2, double val3, char* val4)
{
    Blynk.virtualWrite(pin, val1, val2, val3, val4);
}

void MP_BLYNK_SERIAL_WIFI::writeVirtualPin(uint8_t pin, char* val1)
{
    Blynk.virtualWrite(pin, val1);
}

void MP_BLYNK_SERIAL_WIFI::notify(char* msg) {
    Blynk.notify(msg);
}

bool MP_BLYNK_SERIAL_WIFI::checkVirtualPinValue(uint8_t pin, int value)
{
    return MP_BLYNK_SERIAL_WIFI::value[pin] == value;
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