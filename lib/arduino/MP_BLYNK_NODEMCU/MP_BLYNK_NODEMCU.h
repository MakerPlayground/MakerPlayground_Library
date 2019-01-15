#ifndef MP_BLYNK_NODEMCU_H
#define MP_BLYNK_NODEMCU_H

#include "MP_DEVICE.h"
#include "MP_BLYNK.h"

class MP_BLYNK_NODEMCU : public MP_BLYNK
{
public:
	MP_BLYNK_NODEMCU(char auth[], char ssid[], char pass[]);

	int init();
	void update(unsigned long time);
	void printStatus();
	// static const char* const* ERRORS; // removed since the ERRORS are already declared in MP_BLYNK

	bool isReady();
	int readVirtualPin(uint8_t pin);   // pin = 0-7
	void writeVirtualPin(uint8_t pin, double value);   // pin = 0-7
	void writeVirtualPin(uint8_t pin, int val1, double val2, double val3, char* val4);
	void writeVirtualPin(uint8_t pin, char* val1);
	void notify(char* msg);

	// high level function use by maker playground
	bool checkVirtualPinValue(uint8_t pin, int value);
	int getVirtualPin0();
	int getVirtualPin1();
	int getVirtualPin2();
	int getVirtualPin3();
	int getVirtualPin4();
	int getVirtualPin5();
	int getVirtualPin6();
	int getVirtualPin7();

	// TODO: find alternate implementation as these may be dangerous
	static double value[8];
	static uint8_t valueChanged; // flag indicated that the data has changed

private:
	bool connectWifi();
	char* auth;
	char* ssid;
	char* pass;

	unsigned long lastSendMillis;   // time of the last time we send some data to blynk server
};

#endif
