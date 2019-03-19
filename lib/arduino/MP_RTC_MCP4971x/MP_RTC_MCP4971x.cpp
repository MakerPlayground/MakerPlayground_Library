#include "MP_RTC_MCP4971x.h"
#include "string.h"

#define REFRESH_INTERVAL 50

const char ok[] PROGMEM = "OK";
const char error1[] PROGMEM = "Could not connect to sensor via I2C bus";
const char* const errors_p[] PROGMEM = {ok, error1};

const char* const* MP_RTC_MCP4971x::ERRORS = errors_p;

MP_RTC_MCP4971x::MP_RTC_MCP4971x()
    : rtc(MCP7941x())
{

}

int MP_RTC_MCP4971x::init() {
    rtc.enableClock();
    // TODO: implement sensor connection checking
    return ERR_OK;
}

void MP_RTC_MCP4971x::update(unsigned long current_time) {
    // Do nothing
    if (current_time - lastMillis >= REFRESH_INTERVAL) {
        rtc.getDateTime(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
        lastMillis = current_time;
    }
}

void MP_RTC_MCP4971x::setDateTime(MP_DATETIME t) {
    rtc.setDateTime(t.getSecond(), t.getMinute(), t.getHour(), t.getDayOfWeek(), t.getDate(), t.getMonth(), t.getYear()-2000);
}

bool MP_RTC_MCP4971x::checkDayOfWeek(char* dayName) {
    return (strcmp(dayName, "Sunday") == 0 && dayOfWeek == 1) || 
            (strcmp(dayName, "Monday") == 0 && dayOfWeek == 2) || 
            (strcmp(dayName, "Tuesday") == 0 && dayOfWeek == 3) || 
            (strcmp(dayName, "Wednesday") == 0 && dayOfWeek == 4) || 
            (strcmp(dayName, "Thursday") == 0 && dayOfWeek == 5) || 
            (strcmp(dayName, "Friday") == 0 && dayOfWeek == 6) || 
            (strcmp(dayName, "Saturday") == 0 && dayOfWeek == 7);
}

uint8_t MP_RTC_MCP4971x::getHour() {
    return hour;
}

uint8_t MP_RTC_MCP4971x::getMinute() {
    return minute;
}

uint8_t MP_RTC_MCP4971x::getSecond() {
    return second;
}

uint8_t MP_RTC_MCP4971x::getDate() {
    return dayOfMonth;
}

uint8_t MP_RTC_MCP4971x::getMonth() {
    return month;
}

uint16_t MP_RTC_MCP4971x::getYear() {
    return 2000+year;
}

void MP_RTC_MCP4971x::printStatus() 
{
    if (hour < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(hour, DEC);
    Serial.print(":");

    if (minute < 10)
    {
        Serial.print("0");
    }

    Serial.print(minute, DEC);
    Serial.print(":");

    if (second < 10)
    {
        Serial.print("0");
    }

    Serial.print(second, DEC);
    Serial.print("  ");

    if (dayOfMonth < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(dayOfMonth, DEC);
    Serial.print("/");

    if (month < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(month, DEC);
    Serial.print("/");
    
    Serial.print(year, DEC);

    Serial.print(" (");

    switch(dayOfWeek)
    {
        case 1: 
        Serial.print("Sunday");
        break;

        case 2: 
        Serial.print("Monday");
        break;

        case 3: 
        Serial.print("Tuesday");
        break;

        case 4: 
        Serial.print("Wednesday");
        break;

        case 5: 
        Serial.print("Thursday");
        break;

        case 6: 
        Serial.print("Friday");
        break;

        case 7: 
        Serial.print("Saturday");
        break;
    }

    Serial.println(")");  
}