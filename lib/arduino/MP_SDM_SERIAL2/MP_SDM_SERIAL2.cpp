#include "MP_SDM_SERIAL2.h"

MP_SDM_SERIAL2::MP_SDM_SERIAL2(int baudrate)
	: sdm(SDM(Serial2, baudrate, NOT_A_PIN, SERIAL_8N1, false))
{
}

int MP_SDM_SERIAL2::init()
{
    sdm.begin();
	return MP_ERR_OK;
}

void MP_SDM_SERIAL2::update(unsigned long current_time)
{
    current = sdm.readVal(SDM220T_CURRENT);
    voltage = sdm.readVal(SDM220T_VOLTAGE);
    power = sdm.readVal(SDM220T_POWER);
    frequency = sdm.readVal(SDM220T_FREQUENCY);
    active_apparent_power = sdm.readVal(SDM220T_ACTIVE_APPARENT_POWER);
    reactive_apparent_power = sdm.readVal(SDM220T_REACTIVE_APPARENT_POWER);
    total_active_energy = sdm.readVal(SDM220T_TOTAL_ACTIVE_ENERGY);
    total_reactive_energy = sdm.readVal(SDM220T_TOTAL_REACTIVE_ENERGY);
    power_factor = sdm.readVal(SDM220T_POWER_FACTOR);
    phase_angle = sdm.readVal(SDM220T_PHASE_ANGLE);
}

void MP_SDM_SERIAL2::printStatus()
{
	Serial.print(F("current = "));
	Serial.println(current, 3);
	Serial.print(F("voltage = "));
	Serial.println(voltage, 3);
	Serial.print(F("power = "));
	Serial.println(power, 3);
	Serial.print(F("frequency = "));
	Serial.println(frequency, 3);
	Serial.print(F("active_apparent_power = "));
	Serial.println(active_apparent_power, 3);
	Serial.print(F("reactive_apparent_power = "));
	Serial.println(reactive_apparent_power, 3);
	Serial.print(F("total_active_energy = "));
	Serial.println(total_active_energy, 3);
	Serial.print(F("total_reactive_energy = "));
	Serial.println(total_reactive_energy, 3);
	Serial.print(F("power_factor = "));
	Serial.println(power_factor, 3);
	Serial.print(F("phase_angle = "));
	Serial.println(phase_angle, 3);
}

double MP_SDM_SERIAL2::getCurrent()
{
	return current;
}

double MP_SDM_SERIAL2::getVoltage()
{
	return voltage;
}

double MP_SDM_SERIAL2::getPower()
{
	return power;
}

double MP_SDM_SERIAL2::getFrequency()
{
	return frequency;
}

double MP_SDM_SERIAL2::getActive_Apparent_Power()
{
	return active_apparent_power;
}

double MP_SDM_SERIAL2::getReactive_Apparent_Power()
{
	return reactive_apparent_power;
}

double MP_SDM_SERIAL2::getTotal_Active_Energy()
{
	return total_active_energy;
}

double MP_SDM_SERIAL2::getTotal_Reactive_Energy()
{
	return total_reactive_energy;
}

double MP_SDM_SERIAL2::getPower_Factor()
{
	return power_factor;
}

double MP_SDM_SERIAL2::getPhase_Angle()
{
	return phase_angle;
}
