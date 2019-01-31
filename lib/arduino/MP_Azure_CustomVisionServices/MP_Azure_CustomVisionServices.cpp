#include "MP_Azure_CustomVisionServices.h"

#define CUSTOMVISION_SERVICE_ENDPOINT ".api.cognitive.microsoft.com"   // endpoint should be prepended by region name
#define CUSTOMVISION_SERVICE_PORT 443
#define CUSTOMVISION_REQUEST_INTERVAL 100  // in ms (maximum of 10 requests per second)
#define TIMEOUT 10000   // in ms (maximum time to wait for response from the server)

const char ok[] PROGMEM = "OK";
const char* const errors_p[] PROGMEM = {ok};
const char* const* MP_Azure_CustomVisionServices::ERRORS = errors_p;

using namespace ArduinoJson;

MP_Azure_CustomVisionServices::MP_Azure_CustomVisionServices(String azureRegion, String predictionKey, String projectId, MP_REST* rest)
    : requestEndPoint(azureRegion + CUSTOMVISION_SERVICE_ENDPOINT)
    , predictionKey(predictionKey)
    , projectId(projectId)
    , rest(rest)
    , latestProcessTime(0)
    , error(Error::OK)
{
}

int MP_Azure_CustomVisionServices::init()
{
    return 0;
}

void MP_Azure_CustomVisionServices::update(unsigned long currentTime)
{
}

void MP_Azure_CustomVisionServices::printStatus()
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
            Serial.println(F("Can't connect to Costom Vision services endpoint"));
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

bool MP_Azure_CustomVisionServices::classifiedImage(MP_IMAGE image, String tag, double minProbability)
{
    // process the image iff this function is called for the first time or the image is newer
    if ((this->image.data == NULL || this->image.id != image.id) 
        && (millis() - latestProcessTime) >= CUSTOMVISION_REQUEST_INTERVAL)
    {
        analyzeImage(image);
        if (error != Error::OK)
        {
            return false;
        }
        this->image = image;
        latestProcessTime = millis();
    }

    std::map<String, double>::iterator it = resultTag.find(tag);
    return (it != resultTag.end()) && (it->second >= minProbability);
}

void MP_Azure_CustomVisionServices::analyzeImage(MP_IMAGE image)
{
    if (!rest->isConnected())
    {
        error = Error::NO_INTERNET_CONNECTION;
        return;
    }

    String header;
    header = "POST /customvision/v2.0/Prediction/" + projectId + "/image\r\n";
    header += "Host: ";
    header += requestEndPoint;
    header += "\r\n";
    header += "Content-Type: multipart/form-data\r\n";
    header += "Content-Length: ";
    header += image.size;
    header += "\r\n";
    header += "Prediction-Key: ";
    header += predictionKey;
    header += "\r\n";
    header += "\r\n";

    WiFiClientSecure client;
    if (!client.connect(requestEndPoint.c_str(), CUSTOMVISION_SERVICE_PORT))
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
    JsonArray& tags = root["Predictions"];
    for (auto& node : tags)
    {
        resultTag[String(node["TagName"].as<const char*>())] = node["Probability"];
    }
    /*เรียก jason*/
    error = Error::OK;
}