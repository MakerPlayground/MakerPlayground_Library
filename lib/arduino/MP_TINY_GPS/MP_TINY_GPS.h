#ifndef MP_TINY_GPS_H
#define MP_TINY_GPS_H

#include "MP_DEVICE.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

class MP_TINY_GPS
{
public:
	MP_TINY_GPS(uint8_t tx, uint8_t rx, int baud = 9600);
	int init();
	void update(unsigned long current_time);
	void printStatus();
	static const char* const* ERRORS;

	double getLatitude();
	double getLongitude();

private:
	TinyGPSPlus gps;
	SoftwareSerial ss;
	int GPSBaud;
	double lat = 0.0;
	double lon = 0.0;
	bool isGPSDetected;
	unsigned long lastReadMillis = 0;
};

#endif
