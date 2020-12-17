from es8374 import ES8374
from Maix import I2S
from fpioa_manager import *
from machine import I2C
import audio
import time

import MakerPlayground as mp

class MP_K210_AUDIO_PLAYER:
    def __init__(self):
        self.player = None
        self.volume = 100.0

    def init(self):
        i2c = I2C(I2C.I2C3, freq=600*1000, sda=27, scl=24)
        if ES8374._ES8374_I2CADDR_DEFAULT not in i2c.scan():
            return mp.ERR_CONFIG_DEVICE

        fm.register(13, fm.fpioa.I2S0_MCLK, force=True)
        fm.register(21, fm.fpioa.I2S0_SCLK, force=True)
        fm.register(18, fm.fpioa.I2S0_WS, force=True)
        fm.register(35, fm.fpioa.I2S0_IN_D0, force=True)
        fm.register(34, fm.fpioa.I2S0_OUT_D2, force=True)

        dac = ES8374(i2c)
        dac.setVoiceVolume(100)
        dac.start(0x03)

        self.i2s = I2S(I2S.DEVICE_0, pll2=262144000, mclk=31)
        self.i2s.channel_config(I2S.CHANNEL_2, I2S.TRANSMITTER, resolution=I2S.RESOLUTION_16_BIT,
                                             cycles=I2S.SCLK_CYCLES_32, align_mode=I2S.STANDARD_MODE)

        return mp.ERR_OK

    def update(self, currentTime):
        if self.player:
            if not self.player.play():
                self.player.finish()
                self.player = None

    def printStatus(self):
        pass

    def play(self, filename):
        if self.player:
            self.player.finish()

        self.player = audio.Audio(path='/sd/' + filename)
        self.player.volume(self.volume)
        wav_info = self.player.play_process(self.i2s)
        # print (wav_info)
        self.i2s.set_sample_rate(int(wav_info[1]))

    def setVolume(self, volume):
        self.volume = volume

    def volumeUp(self):
        self.volume += 1
        if self.volume > 100:
            self.volume = 100

    def volumeDown(self):
        self.volume -= 1
        if self.volume < 0:
            self.volume = 0

    def getVolume(self):
        return self.volume