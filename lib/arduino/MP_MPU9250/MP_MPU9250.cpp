#include "MP_MPU9250.h"

#define GRAVITY 9.81

MP_MPU9250::MP_MPU9250()
	: accelMagnitude(0.0)
	, nextUpdateTime(0)
{
}

int MP_MPU9250::init()
{
	Wire.begin();

    imu.calibrateMPU9250(imu.gyroBias, imu.accelBias);
    imu.initMPU9250();
    imu.initAK8963(imu.magCalibration);
	return ERR_OK;
}

void MP_MPU9250::update(unsigned long current_time)
{
	if (nextUpdateTime <= current_time)
	{
        if (imu.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
        {
            imu.readAccelData(imu.accelCount);
            imu.getAres();

            imu.ax = (float)imu.accelCount[0] * imu.aRes; // - accelBias[0];
            imu.ay = (float)imu.accelCount[1] * imu.aRes; // - accelBias[1];
            imu.az = (float)imu.accelCount[2] * imu.aRes; // - accelBias[2];
            accelMagnitude = sqrt(imu.ax*imu.ax + imu.ay*imu.ay + imu.az*imu.az);

            imu.readGyroData(imu.gyroCount);  // Read the x/y/z adc values
            imu.getGres();

            // Calculate the gyro value into actual degrees per second
            // This depends on scale being set
            imu.gx = (float)imu.gyroCount[0] * imu.gRes;
            imu.gy = (float)imu.gyroCount[1] * imu.gRes;
            imu.gz = (float)imu.gyroCount[2] * imu.gRes;

            imu.readMagData(imu.magCount);  // Read the x/y/z adc values
            imu.getMres();

            // Calculate the magnetometer values in milliGauss
            // Include factory calibration per data sheet and user environmental
            // corrections
            // Get actual magnetometer value, this depends on scale being set
            imu.mx = (float)imu.magCount[0] * imu.mRes * imu.magCalibration[0] - imu.magbias[0];
            imu.my = (float)imu.magCount[1] * imu.mRes * imu.magCalibration[1] - imu.magbias[1];
            imu.mz = (float)imu.magCount[2] * imu.mRes * imu.magCalibration[2] - imu.magbias[2];

            imu.tempCount = imu.readTempData();  // Read the adc values
            // Temperature in degrees Centigrade
            imu.temperature = ((float) imu.tempCount) / 333.87 + 21.0;
        }

		nextUpdateTime = current_time + 100;
	}
}

void MP_MPU9250::printStatus()
{
    Serial.print(F("ax,ay,az,amag = "))
	Serial.print(imu.ax);
	Serial.print(F(","));
	Serial.print(imu.ay);
	Serial.print(F(","));
	Serial.print(imu.az);
	Serial.print(F(","));
	Serial.print(accelMagnitude);
	Serial.print(F(" | gx,gy,gz = "));

	Serial.print(imu.gx);
	Serial.print(F(","));
	Serial.print(imu.gy);
	Serial.print(F(","));
	Serial.print(imu.gz);
	Serial.print(F(" | mx,my,mz = "));

	Serial.print(imu.mx);
    Serial.print(F(","));
    Serial.print(imu.my);
    Serial.print(F(","));
    Serial.print(imu.mz);
}

double MP_MPU9250::getAccel_X()
{
	return imu.ax;
}

double MP_MPU9250::getAccel_Y()
{
	return imu.ay;
}

double MP_MPU9250::getAccel_Z()
{
	return imu.az;
}

double MP_MPU9250::getAccel_Magnitude()
{
	return accelMagnitude;
}

double MP_MPU9250::getGyro_X()
{
    return imu.gx;
}

double MP_MPU9250::getGyro_Y()
{	
    return imu.gy;
}

double MP_MPU9250::getGyro_Z()
{
    return imu.gz;
}

double MP_MPU9250::getMag_X()
{
    return imu.mx;
}

double MP_MPU9250::getMag_Y()
{
    return imu.my;
}

double MP_MPU9250::getMag_Z()
{
    return imu.mz;
}

