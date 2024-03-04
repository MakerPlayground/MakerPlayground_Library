# ALLI/O Library

This repository contains the device library for the ALLI/O IDE (formerly known as MakerPlayground IDE)

## Library structure

```
- devices (device definition directory)
    - device id (mfg name + mfg product id)
        - asset
            - device.svg
            - device.png
        - device.json
    - ...
- lib (device shim)
    - platform name e.g. arduino
        - MP_XXX 
        - ...
    - ...
- lib_ext (low-level library)
    - library author e.g. adafruit
        - zip achive of the library e.g. Adafruit_ADXL345.zip
        - ...
    - ...
```

## What is ALLI/O?

[ALLI/O](https://anonymous.4open.science/r/ALLIO_Code) is an integrated development platform for creating electronics project, developing device's firmware, getting your circuit designed and programming your micro-controller board.