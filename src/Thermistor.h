#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>

class Thermistor {

  bool isPowerPinHigh = false;

  uint32_t preparingForMeasurementStartTimestamp = 0;

  double lastTakenTemperatureFahrenheit;

  public:

  uint8_t sensePin;
  uint8_t powerPin;

  Thermistor& setSensePin(uint8_t pin) {
    sensePin = pin;
    return *this;
  };

  Thermistor& setPowerPin(uint8_t pin) {
    powerPin = pin;
    return *this;
  };

  void prepareForMeasurement();

  bool isReadyForMeasurement();

  void takeMeasurement(uint8_t adcResolutionBits);

  double temperatureFahrenheit() {
    return lastTakenTemperatureFahrenheit;
  };

  private:

  double readAbsoluteTemperature(uint8_t adcResolutionBits);
};

#endif // !THERMISTOR_H
