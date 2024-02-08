# CalibrationBoard

Board for contact temperature measurement with the use of thermistors. The board
is intended to be used in calibrating the [IR thermometer board](https://github.com/CrouchingPanda/Thermometer).

## Platform

Originally, ItsyBitsy 32u4 was used, but due to that MCU's insufficient ADC resolution, 
ItsyBitsy nRF52840 Express is now used. The new board has the same form factor and a compatible
pinout, so no modification to the PCB was necessary.

Arduino core used is Adafruit Bluefruit nRF52 v1.6.0.

[InterboardSerial](https://github.com/CrouchingPanda/InterboardSerial) custom library is used 
for communicating with the IR thermometer board.

## Libraries

| Title              | Version |
|--------------------|---------|
| SerialTransfer     | 3.1.3   |
| JLed               | 4.13.1  |
| InterboardSerial   | latest  |

## Theory

Thermistors monitor temperature with resistance. 
[This article](https://learn.adafruit.com/thermistor/using-a-thermistor) by Adafruit explains
the bulk of theory used in creating the PCB as well as making calculations in the software.

