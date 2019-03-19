#include "MP_MPU6050.h"

#define GRAVITY 9.81

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Cannot connect to device";
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_MPU6050::ERRORS = errors_p;

MP_MPU6050::MP_MPU6050(bool ad0high)
	: accel_x(0.0)
	, accel_y(0.0)
	, accel_z(0.0)
	, accel_mag(0.0)
	, gyro_x(0.0)
	, gyro_y(0.0)
	, gyro_z(0.0)
	, accelgyro(MPU6050(ad0high ? 0x69 : 0x68))
{
}

int MP_MPU6050::init()
{
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
#endif

	accelgyro.initialize();
	if (!accelgyro.testConnection())
	{
		return ERR_CONNECT_DEVICE;
	}
	return ERR_OK;
}

void MP_MPU6050::update(unsigned long current_time)
{
	if (next_update_time <= current_time) {
		// the default range is +-2g and the sensor is 16 bits
		accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
		accel_x = (ax / 16384.0) * GRAVITY;
		accel_y = (ay / 16384.0) * GRAVITY;
		accel_z = (az / 16384.0) * GRAVITY;
		accel_mag = sqrt(accel_x*accel_x + accel_y*accel_y + accel_z*accel_z);
		
		// the default range is +-250degree/sec and the sensor is 16 bits
		gyro_x = gx / 32768.0 * 250.0;
		gyro_y = gy / 32768.0 * 250.0;
		gyro_z = gz / 32768.0 * 250.0;

		next_update_time = current_time + 100;
	}
}

void MP_MPU6050::printStatus()
{
	Serial.print(F("accel (x, y, z, mag) = ("));
	Serial.print(accel_x);
	Serial.print(F(","));
	Serial.print(accel_y);
	Serial.print(F(","));
	Serial.print(accel_z);
	Serial.print(F(","));
	Serial.print(accel_mag);
	Serial.println(F(")"));
	
	Serial.print(F("gyro (x, y, z) = ("));
	Serial.print(gyro_x);
	Serial.print(F(","));
	Serial.print(gyro_y);
	Serial.print(F(","));
	Serial.print(gyro_z);
	Serial.println(F(")"));
}

double MP_MPU6050::getAccel_X()
{
	return accel_x;
}

double MP_MPU6050::getAcces_Y()
{
	return accel_y;
}

double MP_MPU6050::getAccel_Z()
{
	return accel_z;
}

double MP_MPU6050::getAccel_Magnitude()
{
	return accel_mag;
}

double MP_MPU6050::getGyro_X()
{
    return gyro_x;
}

double MP_MPU6050::getGyro_Y()
{	
    return gyro_y;
}

double MP_MPU6050::getGyro_Z()
{
    return gyro_z;
}
