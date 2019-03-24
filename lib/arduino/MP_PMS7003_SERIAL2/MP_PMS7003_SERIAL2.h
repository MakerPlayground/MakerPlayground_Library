#ifndef MP_PMS7003_SERIAL2_H
#define MP_PMS7003_SERIAL2_H

#include "MP_DEVICE.h"
#include "PMS.h"

class MP_PMS7003_SERIAL2
{
public:
	MP_PMS7003_SERIAL2();
	int init();
	void update(unsigned long current_time);
	void printStatus();

	uint16_t getAtmospheric_PM_1_0();
	uint16_t getAtmospheric_PM_2_5();
	uint16_t getAtmospheric_PM_10();

	bool isDataValid();
	bool isDataInvalid();

private:
	PMS pms;
	PMS::DATA data;
	bool isDataCorrected;
	unsigned long lastReadSuccess;
};

#endif
