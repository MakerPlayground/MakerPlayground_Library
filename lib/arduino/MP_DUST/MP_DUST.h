#ifndef MP_DUST_H
#define MP_DUST_H

#include "MP_DEVICE.h"
#include "SoftwareSerial.h"

class MP_DUST
{
public:
	MP_DUST(uint8_t gps_tx, uint8_t gps_rx, int baud = 9600);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getPM_2_5();
	bool isDataValid();
	bool isDataInvalid();

private:
    unsigned long lastQMillis = 0;
	SoftwareSerial ss;
	uint8_t data[9];
	int dustBaud;
	double PM25 = 0.0;
	bool isDataCorrected;
	const byte configCommand[10] = {0x00,0XFF,0x01,0x78,0x41,0x00,0x00,0x00,0x00,0x46};
	const byte sensorCommand[10] = {0x00,0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
};

#endif
