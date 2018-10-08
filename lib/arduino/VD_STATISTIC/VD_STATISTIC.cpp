#include "VD_STATISTIC.h"

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};

const char* const* VD_STATISTIC::ERRORS = errors_p;

#define returnIfDataExist(val, default_val) return N != 0 ? val : default_val;

VD_STATISTIC::VD_STATISTIC()
{
}

int VD_STATISTIC::init() 
{
    return 0;
}

void VD_STATISTIC::update(unsigned long current_time) 
{

}

void VD_STATISTIC::printStatus()
{
    Serial.print("count: ");
    Serial.println(N);

    Serial.print("average: ");
    Serial.println(getAverage());

    Serial.print("SD: ");
    Serial.println(getSD());

    Serial.print("variance: ");
    Serial.println(getVariance());
}

void VD_STATISTIC::addData(double value) {
    N += 1;
    sum += value;
    sum_sq += pow(value, 2);

    average = sum / N;
	variance = sum_sq / N - pow(sum / N, 2);
	SD = sqrt(variance);
}

unsigned long VD_STATISTIC::getCount() {
    return N;
}

double VD_STATISTIC::getAverage() {
    returnIfDataExist(average, 0.0);
}

double VD_STATISTIC::getSD() {
    returnIfDataExist(SD, 0.0);
}

double VD_STATISTIC::getVariance() {
    returnIfDataExist(variance, 0.0);
}