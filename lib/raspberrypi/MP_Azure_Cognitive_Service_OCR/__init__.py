from MakerPlayground.Devices.MP_Device import MP_Device
import os, requests, time
import pygame
import io
from xml.etree import ElementTree

class MP_Azure_Cognitive_Service_OCR(MP_Device):
    # properties: region, service_subscription_key, word_per_minute
    def __init__(self, region, service_subscription_key, max_translations_per_minute):
        self.min_seconds_wait_per_translation = 60.0 / max_translations_per_minute
        self.ocrUrl = "https://{0}.api.cognitive.microsoft.com/vision/v2.0/ocr".format(region)
        self.subscription_key = service_subscription_key
        self.access_token = None

        self.last_token_time = 0
        self.last_translation_time = 0

        self.text = ""

    def update(self, currentTime):
        pass

    def getStatus(self):
        return "Device is working..."

    def convertToText(self, image):
        currentTime = time.time()
        if currentTime - self.last_translation_time < self.min_seconds_wait_per_translation:
            return

        try:
            # compressed image to jpeg binary
            stream = io.BytesIO()
            image.save(stream, format="jpeg")
            stream.seek(0)

            # define HTTP headers, URL params (query string) and body
            headers = {
                'Ocp-Apim-Subscription-Key': self.subscription_key,
                'Content-Type': 'application/octet-stream'
            }
            params = {
                'language': 'unk',
                'detectOrientation': 'true'
            }
            body = stream.read()

            # make a request
            response = requests.post(self.ocrUrl, headers=headers, data=body, timeout=3)

            # get the result
            if response.status_code == 200:
                analysis = response.json()
                # Extract the word bounding boxes and text.
                line_infos = [region["lines"] for region in analysis["regions"]]
                word_infos = []
                for line in line_infos:
                    for word_metadata in line:
                        for word_info in word_metadata["words"]:
                            word_infos.append(word_info["text"])
                self.text = " ".join(word_infos)
            
            else:
                self.text = "Error {0}".format(response.status_code)
            
            self.last_translation_time = currentTime

        except requests.Timeout:
            self.text = ""

    def convertToTextFile(self, image, file_name):
        currentTime = time.time()
        if currentTime - self.last_translation_time < self.min_seconds_wait_per_translation:
            return

        self.convertToText(image)

        with open(file_name, 'w') as fp:
            print(self.text, file=fp)

    def hasText(self):
        return self.text != ""

    def hasNoText(self):
        return self.text == ""

    def getText(self):
        return self.text