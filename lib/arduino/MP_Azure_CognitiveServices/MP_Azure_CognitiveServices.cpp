#include "MP_Azure_CognitiveServices.h"

#define COGNITIVE_SERVICE_ENDPOINT ".api.cognitive.microsoft.com"   // endpoint should be prepended by region name
#define COGNITIVE_SERVICE_PORT 443
#define COGNITIVE_REQUEST_INTERVAL 100  // in ms (maximum of 10 requests per second)
#define TIMEOUT 10000   // in ms (maximum time to wait for response from the server)

using namespace ArduinoJson;

MP_Azure_CognitiveServices::MP_Azure_CognitiveServices(String azureRegion, String key, double requestInterval, MP_AZURE* rest)
    : requestEndPoint(azureRegion + COGNITIVE_SERVICE_ENDPOINT)
    , key(key)
    , requestInterval(requestInterval * 1000)   // convert from sec to ms
    , rest(rest)
    , latestProcessTime(0)
    , error(Error::OK)
{
}

int MP_Azure_CognitiveServices::init()
{
    return MP_ERR_OK;
}

void MP_Azure_CognitiveServices::update(unsigned long currentTime)
{
}

void MP_Azure_CognitiveServices::printStatus()
{
    switch (error) 
    {
        case Error::OK:
            for (const auto& tag : resultTag)
            {
                Serial.print(tag.first);
                Serial.print("(");
                Serial.print(tag.second);
                Serial.print(") ");
            }
            Serial.print("last updated: ");
            Serial.println(latestProcessTime);
            break;
        case Error::NO_INTERNET_CONNECTION:
            Serial.println(F("Wifi is not connected"));
            break;
        case Error::CANT_CONNECT_AZURE:
            Serial.println(F("Can't connect to cognitive services endpoint"));
            break;
        case Error::SERVER_ERROR:
            Serial.println(F("Got error reponse code from the server"));
            break;
        case Error::INVALID_RESPONSE:
            Serial.println(F("Got invalid response from the server"));
            break;
        case Error::CANT_PARSE_JSON:
            Serial.println(F("Can't parse the response from the server"));
            break;
    }
}

bool MP_Azure_CognitiveServices::classifiedImage(MP_IMAGE image, String tag, double minProbability)
{
    // process the image iff this function is called for the first time or the image is newer
    unsigned long timeElapsed = millis() - latestProcessTime;
    if ((this->image.data == NULL || this->image.id != image.id) 
        && timeElapsed >= COGNITIVE_REQUEST_INTERVAL
        && timeElapsed >= requestInterval)
    {
        analyzeImage(image);
        if (error != Error::OK)
        {
            return false;
        }
        this->image = image;
        latestProcessTime = millis();
    }

    if (tag.indexOf(',') == -1)
    {
        std::map<String, double>::iterator it = resultTag.find(tag);
        return (it != resultTag.end()) && (it->second >= minProbability);
    }
    else
    {
        char* tmp = strdup(tag.c_str());
        tmp = strtok(tmp, ",");
        while (tmp != NULL)
        {
            std::map<String, double>::iterator it = resultTag.find(String(tmp));
            if ((it == resultTag.end()) || (it->second < minProbability))
            {
                return false;
            }
            tmp = strtok(NULL, ",");
        }
        return true;
    }
}

bool MP_Azure_CognitiveServices::noDetectedImage(MP_IMAGE image, String tag, double minProbability)
{
    // process the image iff this function is called for the first time or the image is newer
    unsigned long timeElapsed = millis() - latestProcessTime;
    if ((this->image.data == NULL || this->image.id != image.id)
        && timeElapsed >= COGNITIVE_REQUEST_INTERVAL
        && timeElapsed >= requestInterval)
    {
        analyzeImage(image);
        if (error != Error::OK)
        {
            return false;
        }
        this->image = image;
        latestProcessTime = millis();
    }

    if (tag.indexOf(',') == -1)
        {
            std::map<String, double>::iterator it = resultTag.find(tag);
            return (it == resultTag.end()) && (it->second >= minProbability);
        }
        else
        {
            char* tmp = strdup(tag.c_str());
            tmp = strtok(tmp, ",");
            while (tmp != NULL)
            {
                std::map<String, double>::iterator it = resultTag.find(String(tmp));
                if ((it != resultTag.end()) && (it->second >= minProbability))
                {
                    return false;
                }
                tmp = strtok(NULL, ",");
            }
            return true;
        }
}


void MP_Azure_CognitiveServices::analyzeImage(MP_IMAGE image)
{
    // clear result map first so classifiedImage won't reused old result when this function fails
    resultTag.clear();

    if (!rest->isConnected())
    {
        error = Error::NO_INTERNET_CONNECTION;
        return;
    }

    String header;
    header = "POST /vision/v1.0/analyze?visualFeatures=Tags&language=en HTTP/1.1\r\n";
    header += "Host: ";
    header += requestEndPoint;
    header += "\r\n";
    header += "Content-Type: application/octet-stream\r\n";
    header += "Content-Length: ";
    header += image.size;
    header += "\r\n";
    header += "Ocp-Apim-Subscription-Key: ";
    header += key;
    header += "\r\n";
    header += "\r\n";

    WiFiClientSecure client;
    if (!client.connect(requestEndPoint.c_str(), COGNITIVE_SERVICE_PORT))
    {
        error = Error::CANT_CONNECT_AZURE;
        return;
    }

    client.print(header);
    client.write(image.data, image.size);
    client.print("\r\n");

    // check http status
    String status = client.readStringUntil('\r');
    if (!status.equals("HTTP/1.1 200 OK"))
    {
        error = Error::SERVER_ERROR;
        return;
    }

    // skip http header
    if (!client.find("\r\n\r\n"))
    {
        error = Error::INVALID_RESPONSE;
        return;
    }

    // parse JSON object
    DynamicJsonBuffer jsonBuffer(2048);
    JsonObject& root = jsonBuffer.parseObject(client);
    if (!root.success()) {
        error = Error::CANT_PARSE_JSON;
        return;
    }
    JsonArray& tags = root["tags"];
    for (auto& node : tags)
    {
        resultTag[String(node["name"].as<const char*>())] = (node["probability"].as<double>() * 100.0);
    }

    error = Error::OK;
}