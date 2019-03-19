#ifndef MP_TINY_GPS_H
#define MP_TINY_GPS_H

#include "MP_DEVICE.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

class MP_TINY_GPS
{
public:
	MP_TINY_GPS(uint8_t gps_tx, uint8_t gps_rx, int baud = 9600);
	int init();
	void update(unsigned long current_time);
	void printStatus();

	double getLatitude();
	double getLongitude();
	bool isDataValid();
	bool isDataInvalid();

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
