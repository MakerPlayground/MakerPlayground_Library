#ifndef MP_7SEG_SOFTSERIAL_H
#define MP_7SEG_SOFTSERIAL_H

#include "MP_DEVICE.h"
#include "SendOnlySoftwareSerial.h"

class MP_7SEG_SOFTSERIAL
{
public:
	MP_7SEG_SOFTSERIAL(uint8_t tx);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;
	
	void showValue(double num);
	void showData(double num);
	void off();

private:
	void sendInvalid();
	void showFloat(double num);
	void sendData(int num, uint8_t dot, bool negative);
	SendOnlySoftwareSerial serial;
	double valueToShow;
};

#endif
