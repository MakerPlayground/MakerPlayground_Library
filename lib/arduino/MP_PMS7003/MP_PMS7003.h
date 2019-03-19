#ifndef MP_PMS7003_H
#define MP_PMS7003_H

#include "MP_DEVICE.h"
#include "SoftwareSerial.h"
#include "PMS.h"

class MP_PMS7003
{
public:
	MP_PMS7003(uint8_t dust_tx, uint8_t dust_rx);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	uint16_t getAtmospheric_PM_1_0();
	uint16_t getAtmospheric_PM_2_5();
	uint16_t getAtmospheric_PM_10();

	bool isDataValid();
	bool isDataInvalid();

private:
	SoftwareSerial ss;
	PMS pms;
	PMS::DATA data;
	bool isDataCorrected;
	unsigned long lastReadSuccess;
};

#endif
