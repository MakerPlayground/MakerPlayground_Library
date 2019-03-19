#ifndef MP_WINSEN_ZH03_H
#define MP_WINSEN_ZH03_H

#include "MP_DEVICE.h"
#include "SoftwareSerial.h"

class MP_WINSEN_ZH03
{
public:
	MP_WINSEN_ZH03(uint8_t dust_tx, uint8_t dust_rx, int baud = 9600);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	uint16_t getAtmospheric_PM_1_0();
	uint16_t getAtmospheric_PM_2_5();
	uint16_t getAtmospheric_PM_10();

	bool isDataValid();
	bool isDataInvalid();

private:
    unsigned long lastQMillis = 0;
	SoftwareSerial ss;
	uint8_t data[9];
	int dustBaud;
	uint16_t PM1_0 = 0.0;
	uint16_t PM2_5 = 0.0;
	uint16_t PM10 = 0.0;
	bool isDataCorrected;
	const byte configCommand[10] = {0x00,0XFF,0x01,0x78,0x41,0x00,0x00,0x00,0x00,0x46}; // Q&A mode
	const byte sensorCommand[10] = {0x00,0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79}; // Question
};

#endif
