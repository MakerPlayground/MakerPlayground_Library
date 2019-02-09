from MakerPlayground.Devices.MP_Device import MP_Device
import os, requests, time
import pygame
from xml.etree import ElementTree

class MP_Azure_Cognitive_Service_TTS(MP_Device):
    # properties: region, speech_service_name, service_subscription_key, word_per_minute
    def __init__(self, region, speech_service_name, service_subscription_key, max_translations_per_minute):
        self.min_seconds_wait_per_translation = 60.0 / max_translations_per_minute
        self.issueTokenUrl = "https://{0}.api.cognitive.microsoft.com/sts/v1.0/issuetoken".format(region)
        self.ttsUrl = "https://{0}.tts.speech.microsoft.com/cognitiveservices/v1".format(region)
        self.speech_service_name = speech_service_name
        self.subscription_key = service_subscription_key
        self.access_token = None

        self.last_token_time = 0
        self.last_translation_time = 0
        self.text = ""

    def update(self, currentTime):
        pass

    def getStatus(self):
        return "lastest text: {0}".format(self.text)

    def _get_token(self):
        try:
            headers = { 'Ocp-Apim-Subscription-Key': self.subscription_key }
            response = requests.post(self.issueTokenUrl, headers=headers, timeout=0.25)
            if response.text is not None:
                self.access_token = str(response.text)
                return True
        except requests.Timeout:
            pass
        return False

    def convertToSoundFile(self, text, save_file_name):
        currentTime = time.time()
        if currentTime - self.last_translation_time < self.min_seconds_wait_per_translation:
            return

        if currentTime - self.last_token_time >= 9.0:
            if self._get_token():
                self.last_token_time = currentTime
            else:
                return

        self.text = text
        
        if text == "":
            return
            
        headers = {
            'Authorization': 'Bearer ' + self.access_token,
            'Content-Type': 'application/ssml+xml',
            'X-Microsoft-OutputFormat': 'riff-24khz-16bit-mono-pcm',
            'User-Agent': self.speech_service_name
        }
        xml_body = ElementTree.Element('speak', version='1.0')
        xml_body.set('{http://www.w3.org/XML/1998/namespace}lang', 'en-us')
        voice = ElementTree.SubElement(xml_body, 'voice')
        voice.set('{http://www.w3.org/XML/1998/namespace}lang', 'en-US')
        voice.set('name', 'Microsoft Server Speech Text to Speech Voice (en-US, Guy24KRUS)')
        voice.text = text
        body = ElementTree.tostring(xml_body)

        try:
            response = requests.post(self.ttsUrl, headers=headers, data=body, timeout=3)
            if response.status_code == 200:
                with open(save_file_name, 'wb') as audio:
                    audio.write(response.content)
            self.last_translation_time = currentTime
        except requests.Timeout:
            pass

    def convertAndPlaySound(self, text):
        if time.time() - self.last_translation_time < self.min_seconds_wait_per_translation:
            return

        dummy_sound_file = "__.wav"
        self.convertToSoundFile(text, dummy_sound_file)
        if os.path.exists(dummy_sound_file):
            pygame.mixer.init()
            pygame.mixer.music.load(dummy_sound_file)
            pygame.mixer.music.play()
            os.remove(dummy_sound_file)

