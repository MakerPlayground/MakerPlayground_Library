#ifndef MP_7SEG_SOFTSERIAL_H
#define MP_7SEG_SOFTSERIAL_H

#include "MP_DEVICE.h"

#if defined(ARDUINO_ARCH_AVR)
	#include "SendOnlySoftwareSerial.h"
#elif defined(ARDUINO_ARCH_ESP8266)
	#include "SoftwareSerial.h"
#endif

class MP_7SEG_SOFTSERIAL
{
public:
	MP_7SEG_SOFTSERIAL(uint8_t tx);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	
	void showTwoIntWithColon(int8_t beforeColon, int8_t afterColon);
	void showData(double num);
	void off();

private:
	void sendInvalid();
	void showFloat(double num);
	void sendData(int num, uint8_t dot, bool negative);
#if defined(ARDUINO_ARCH_AVR)
	SendOnlySoftwareSerial serial;
#elif defined(ARDUINO_ARCH_ESP8266)
	SoftwareSerial serial;
#endif
	String valueToShow;
};

#endif
