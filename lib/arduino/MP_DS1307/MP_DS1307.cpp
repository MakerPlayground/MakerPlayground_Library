#include "MP_DS1307.h"
#include "string.h"

#define REFRESH_INTERVAL 50

MP_DS1307::MP_DS1307()
    : Rtc(Wire)
{

}

int MP_DS1307::init() {
    Rtc.Begin();
    if (!Rtc.GetIsRunning())
    {
        Rtc.SetIsRunning(true);
    }
    Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low); 
    return ERR_OK;
}

void MP_DS1307::update(unsigned long current_time) {
    if (current_time - lastMillis >= REFRESH_INTERVAL) {
        if (Rtc.IsDateTimeValid()) {
            isValid = true;
            now = Rtc.GetDateTime();
        }
        else {
            isValid = false;
        }
        lastMillis = current_time;
    }
}

void MP_DS1307::setDateTime(MP_DATETIME t) {
    Rtc.SetDateTime(RtcDateTime(t.getYear(), t.getMonth(), t.getDate(), t.getHour(), t.getMinute(), t.getSecond()));
}

bool MP_DS1307::checkDayOfWeek(uint8_t day) {
    return now.DayOfWeek() == day-1;  // Reindex Sunday = 1 -> 0, Saturday = 7 -> 6
}

uint8_t MP_DS1307::getHour() {
    return now.Hour();
}

uint8_t MP_DS1307::getMinute() {
    return now.Minute();
}

uint8_t MP_DS1307::getSecond() {
    return now.Second();
}

uint8_t MP_DS1307::getDate() {
    return now.Day();
}

uint8_t MP_DS1307::getMonth() {
    return now.Month();
}

uint16_t MP_DS1307::getYear() {
    return now.Year();
}

void MP_DS1307::printStatus() 
{
    if (!isValid) {
        Serial.print(F("DateTime is not valid"));
        return;
    }

    if (now.Hour() < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(now.Hour(), DEC);
    Serial.print(":");

    if (now.Minute() < 10)
    {
        Serial.print("0");
    }

    Serial.print(now.Minute(), DEC);
    Serial.print(":");

    if (now.Second() < 10)
    {
        Serial.print("0");
    }

    Serial.print(now.Second(), DEC);
    Serial.print("  ");

    if (now.Day() < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(now.Day(), DEC);
    Serial.print("/");

    if (now.Month() < 10)
    {
        Serial.print("0");
    }
    
    Serial.print(now.Month(), DEC);
    Serial.print("/");
    
    Serial.print(now.Year(), DEC);

    Serial.print(" (");

    switch(now.DayOfWeek())
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