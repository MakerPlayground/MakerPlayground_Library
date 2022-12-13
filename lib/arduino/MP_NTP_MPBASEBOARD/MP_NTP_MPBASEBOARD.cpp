#include "MP_NTP_MPBASEBOARD.h"

#define REFRESH_INTERVAL 1000

MP_NTP_MPBASEBOARD::MP_NTP_MPBASEBOARD()
{
}

int MP_NTP_MPBASEBOARD::init() {
    Serial1.println(F("I\r"));
    if (!checkResponse())
    {
        return MP_ERR_CONNECT_SERVER;
    }
    return MP_ERR_OK;
}

bool MP_NTP_MPBASEBOARD::checkResponse()
{
    return Serial1.readStringUntil('\n').equals("OK\r");
}

void MP_NTP_MPBASEBOARD::update(unsigned long current_time) {
    // Do nothing
    if (current_time - lastMillis >= REFRESH_INTERVAL) {
        Serial1.println(F("T\r"));
        if (!checkResponse())
        {
            return MP_ERR_CONNECT_SERVER;
        }
        date = Serial1.parseInt();
        month = Serial1.parseInt();
        year = Serial1.parseInt();
        hour = Serial1.parseInt();
        minute = Serial1.parseInt();
        second = Serial1.parseInt();
        if (!checkResponse())
        {
            return MP_ERR_CONNECT_SERVER;
        }
        lastMillis = current_time;
    }
}

uint8_t MP_NTP_MPBASEBOARD::getHour() {
    return hour;
}

uint8_t MP_NTP_MPBASEBOARD::getMinute() {
    return minute;
}

uint8_t MP_NTP_MPBASEBOARD::getSecond() {
    return second;
}

uint8_t MP_NTP_MPBASEBOARD::getDate() {
    return date;
}

uint8_t MP_NTP_MPBASEBOARD::getMonth() {
    return month;
}

uint16_t MP_NTP_MPBASEBOARD::getYear() {
    // TODO: need to fix constant value
    return year + 1792;
}

void MP_NTP_MPBASEBOARD::printStatus()
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

    if (date < 10)
    {
        Serial.print("0");
    }

    Serial.print(date, DEC);
    Serial.print("/");

    if (month < 10)
    {
        Serial.print("0");
    }

    Serial.print(month, DEC);
    Serial.print("/");

    Serial.print(year, DEC);
}