#ifndef MP_SDM_SOFTSERIAL_H
#define MP_SDM_SOFTSERIAL_H

#include "MP_DEVICE.h"
#include "SoftwareSerial.h"
#include "SDM.h"

class MP_SDM_SOFTSERIAL
{
public:
	MP_SDM_SOFTSERIAL(uint8_t device_tx, uint8_t device_rx, int baudrate);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getCurrent();
	double getVoltage();
	double getPower();
	double getFrequency();
	double getActive_Apparent_Power();
	double getReactive_Apparent_Power();
	double getTotal_Active_Energy();
	double getTotal_Reactive_Energy();
	double getPower_Factor();
	double getPhase_Angle();

private:
    SoftwareSerial ss;
	SDM sdm;
	double current = 0.0;
	double voltage = 0.0;
	double power = 0.0;
	double frequency = 0.0;
	double active_apparent_power = 0.0;
	double reactive_apparent_power = 0.0;
	double total_active_energy = 0.0;
	double total_reactive_energy = 0.0;
	double power_factor = 0.0;
	double phase_angle = 0.0;
};

#endif
