# Maker Playground Library

This repository contains the device library for the Maker Playground IDE

## Library structure

- devices
    - device id (mfg name + mfg product id)
        - asset
            - device.svg
            - device.png
        - device.json
    - ...
- lib
    - platform name e.g. arduino
        - MP_XXX e.g. MP_LED_AH (Library for each type of device which may be used by one or more devices from any manufacturer. The library may be self-contatined or included some libraries in lib_ext)
        - ...
    - ...
- lib_ext
    - library author e.g. adafruit
        - zip achive of the library e.g. Adafruit_ADXL345.zip
        - ...
    - ...

## What is Maker Playground?

[Maker Playground](https://github.com/InGarage/MakerPlayGround) is an integrated development platform for creating electronics project, developing device's firmware, getting your circuit designed and programming your micro-controller board.