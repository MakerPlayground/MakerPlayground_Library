#include "MP_PCF85063TP.h"
#include "string.h"

#define REFRESH_INTERVAL 500

MP_PCF85063TP::MP_PCF85063TP()
{

}

int MP_PCF85063TP::init() {
    RTclock.begin();
    // uint8_t ret = RTclock.calibratBySeconds(0, -0.000041);
    return MP_ERR_OK;
}

void MP_PCF85063TP::update(unsigned long current_time) {
    if (current_time - lastMillis >= REFRESH_INTERVAL) {
        RTclock.getTime();
        lastMillis = current_time;
    }
}

void MP_PCF85063TP::setDateTime(const char * date_time) {
    MP_DATETIME t = MP_DATETIME(date_time);
    
    RTclock.stopClock();
    RTclock.fillByYMD(t.getYear(),t.getMonth(),t.getDate());
    RTclock.fillByHMS(t.getHour(),t.getMinute(),t.getSecond());
    RTclock.fillDayOfWeek(t.getDayOfWeek()-1); // convert
    RTclock.setTime();
    RTclock.startClock();
}

bool MP_PCF85063TP::checkDayOfWeek(uint8_t day) {
    return RTclock.dayOfWeek + 1 == day;  // Reindex Sunday = 1 -> 0, Saturday = 7 -> 6
}

uint8_t MP_PCF85063TP::getHour() {
    return RTclock.hour;
}

uint8_t MP_PCF85063TP::getMinute() {
    return RTclock.minute;
}

uint8_t MP_PCF85063TP::getSecond() {
    return RTclock.second;
}

uint8_t MP_PCF85063TP::getDate() {
    return RTclock.dayOfMonth;
}

uint8_t MP_PCF85063TP::getMonth() {
    return RTclock.month;
}

uint16_t MP_PCF85063TP::getYear() {
    return RTclock.year + 2000;
}

void MP_PCF85063TP::printStatus() 
{
    if (!isValid) {
        Serial.print(F("DateTime is not valid"));
        return;
    }

    if (RTclock.hour < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(RTclock.hour, DEC);
    Serial.print(":");

    if (RTclock.minute < 10)
    {
        Serial.print("0");
    }

    Serial.print(RTclock.minute, DEC);
    Serial.print(":");

    if (RTclock.second < 10)
    {
        Serial.print("0");
    }

    Serial.print(RTclock.second, DEC);
    Serial.print("  ");

    if (RTclock.dayOfMonth < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(RTclock.dayOfMonth, DEC);
    Serial.print("/");

    if (RTclock.month < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(RTclock.month, DEC);
    Serial.print("/");
    
    Serial.print(RTclock.year + 2000, DEC);

    Serial.print(" (");

    switch(RTclock.dayOfWeek)
    {
        case 0: 
        Serial.print("Sunday");
        break;

        case 1: 
        Serial.print("Monday");
        break;

        case 2: 
        Serial.print("Tuesday");
        break;

        case 3: 
        Serial.print("Wednesday");
        break;

        case 4: 
        Serial.print("Thursday");
        break;

        case 5: 
        Serial.print("Friday");
        break;

        case 6: 
        Serial.print("Saturday");
        break;
    }

    Serial.println(")");  
}