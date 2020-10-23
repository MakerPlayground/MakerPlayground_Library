#include "MP_HPM32322550_SOFTSERIAL.h"

MP_HPM32322550_SOFTSERIAL::MP_HPM32322550_SOFTSERIAL(uint8_t dust_tx, uint8_t dust_rx)
	: pm25_ser(SoftwareSerial(dust_tx, dust_rx))
	, lastReadSuccess(0)
{
}

int MP_HPM32322550_SOFTSERIAL::init()
{
  pm25_ser.begin(9600);
  PM25.init(&pm25_ser, 0x00, []{});
	return MP_ERR_OK;
}

void MP_HPM32322550_SOFTSERIAL::printStatus()
{
}

void MP_HPM32322550_SOFTSERIAL::update(unsigned long current_time)
{
  if (current_time - lastReadSuccess > 500)
	{
    PM25.read();
    lastReadSuccess = current_time;
	}
}

bool MP_HPM32322550_SOFTSERIAL::isDataValid()
{
	return true;
}

bool MP_HPM32322550_SOFTSERIAL::isDataInvalid()
{
	return false;
}

uint16_t MP_HPM32322550_SOFTSERIAL::getAtmospheric_PM_2_5()
{
	return PM25.get(PM25_TYPE);
}

uint16_t MP_HPM32322550_SOFTSERIAL::getAtmospheric_PM_10()
{
	return PM25.get(PM10_TYPE);
}
