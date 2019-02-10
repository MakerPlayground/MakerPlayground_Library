#ifndef MP_AZURE_COGNITIVESERVICES_H
#define MP_AZURE_COGNITIVESERVICES_H

#include "MP_DEVICE.h"
#include "MP_AZURE.h"
#include <WiFiClientSecure.h>
#include <map>
#include <ArduinoJson.hpp>

class MP_Azure_CognitiveServices
{
public:
    MP_Azure_CognitiveServices(String azureRegion, String key, double requestInterval, MP_AZURE* rest);
    int init();
	void update(unsigned long currentTime);
	void printStatus();
	static const char* const* ERRORS;

    bool classifiedImage(MP_IMAGE image, String tag, double minProbability);
    bool noDetectedImage(MP_IMAGE image, String tag, double minProbability);

    enum class Error
    {
        OK,
        NO_INTERNET_CONNECTION,
        CANT_CONNECT_AZURE,
        SERVER_ERROR,
        INVALID_RESPONSE,
        CANT_PARSE_JSON
    };

private:
    void analyzeImage(MP_IMAGE image);

    String requestEndPoint;
    String key;
    int requestInterval;    // user defined minimum time to wait before next request (in ms)
    MP_AZURE* rest;

    MP_IMAGE image;
    std::map<String, double> resultTag;
    unsigned long latestProcessTime;
    Error error;
};

#endif