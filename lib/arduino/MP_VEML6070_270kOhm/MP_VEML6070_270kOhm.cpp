#include "MP_VEML6070_270kOhm.h"

MP_VEML6070_270kOhm::MP_VEML6070_270kOhm(uint8_t readingMode)
    : uv(Adafruit_VEML6070())
    , uvIndex(0.0)
    , nextReading(0)
    , readingMode(readingMode)
{
}

int MP_VEML6070_270kOhm::init()
{
    if(readingMode == 1) {
        uv.begin(VEML6070_1_T);
    } else if(readingMode == 2) {
        uv.begin(VEML6070_2_T);
    } else if(readingMode == 3) {
        uv.begin(VEML6070_4_T);
    }
	return MP_ERR_OK;
}

void MP_VEML6070_270kOhm::update(unsigned long current_time) 
{
    if (current_time >= nextReading)
    {
        nextReading = current_time + 50;        // next reading should happen at least 50ms later otherwise the sound
        value = uv.readUV();
        convergeValue();
    }
}

bool MP_VEML6070_270kOhm::checkRiskLevel(uint8_t risk)
{
    if(uvIndex >= 0 && uvIndex <= 2) {
        if(risk == 1) {
            return true;
        }
    } else if(uvIndex >= 3 && uvIndex <= 5) {
        if(risk == 2) {
            return true;
        }
    } else if(uvIndex >= 6 && uvIndex <= 7) {
        if(risk == 3) {
            return true;
        }
    } else if(uvIndex >= 8 && uvIndex <= 10) {
        if(risk == 4) {
            return true;
        }
    } else if(uvIndex > 10) {
        if(risk == 5) {
            return true;
        }
    }

    return false; 
}

uint8_t MP_VEML6070_270kOhm::getUV_Index()
{ 
	return uvIndex;
}

void MP_VEML6070_270kOhm::printStatus()
{
	Serial.print(F("UV Index = "));
	Serial.print(uvIndex);
}

void MP_VEML6070_270kOhm::convergeValue()
{
    if(readingMode == 1) {
        if(value >= 0 && value <= 186) {
            uvIndex = 0;
        } else if(value >= 187 && value <= 372) {
            uvIndex = 1;
        } else if(value >= 373 && value <= 560) {
            uvIndex = 2;
        } else if(value >= 561 && value <= 747) {
            uvIndex = 3;
        } else if(value >= 748 && value <= 933) {
            uvIndex = 4;
        } else if(value >= 934 && value <= 1120) {
            uvIndex = 5;
        } else if(value >= 1121 && value <= 1307) {
            uvIndex = 6;
        } else if(value >= 1306 && value <= 1494) {
            uvIndex = 7;
        } else if(value >= 1495 && value <= 1681) {
            uvIndex = 8;
        } else if(value >= 1682 && value <= 1868) {
            uvIndex = 9;
        } else if(value >= 1869 && value <= 2055) {
            uvIndex = 10;
        } else if(value > 2055) {
            uvIndex = 11;
        } else {
            uvIndex = 0;
        }
    } else if(readingMode == 2) {
        if(value >= 0 && value <= 373) {
            uvIndex = 0;
        } else if(value >= 374 && value <= 747) {
            uvIndex = 1;
        } else if(value >= 748 && value <= 1120) {
            uvIndex = 2;
        } else if(value >= 1121 && value <= 1494) {
            uvIndex = 3;
        } else if(value >= 1495 && value <= 1868) {
            uvIndex = 4;
        } else if(value >= 1869 && value <= 2241) {
            uvIndex = 5;
        } else if(value >= 2242 && value <= 2615) {
            uvIndex = 6;
        } else if(value >= 2616 && value <= 2988) {
            uvIndex = 7;
        } else if(value >= 2989 && value <= 3362) {
            uvIndex = 8;
        } else if(value >= 3363 && value <= 3735) {
            uvIndex = 9;
        } else if(value >= 3736 && value <= 4108) {
            uvIndex = 10;
        } else if(value > 4108) {
            uvIndex = 11;
        } else {
            uvIndex = 0;
        }
    } else if(readingMode == 3) {
        if(value >= 0 && value <= 746) {
            uvIndex = 0;
        } else if(value >= 747 && value <= 1493) {
            uvIndex = 1;
        } else if(value >= 1494 && value <= 2240) {
            uvIndex = 2;
        } else if(value >= 2241 && value <= 2987) {
            uvIndex = 3;
        } else if(value >= 2988 && value <= 3734) {
            uvIndex = 4;
        } else if(value >= 3735 && value <= 4482) {
            uvIndex = 5;
        } else if(value >= 4483 && value <= 5229) {
            uvIndex = 6;
        } else if(value >= 5230 && value <= 5976) {
            uvIndex = 7;
        } else if(value >= 5977 && value <= 6723) {
            uvIndex = 8;
        } else if(value >= 6724 && value <= 7469) {
            uvIndex = 9;
        } else if(value >= 7470 && value <= 8216) {
            uvIndex = 10;
        } else if(value > 8216) {
            uvIndex = 11;
        } else {
            uvIndex = 0;
        }
    }
}