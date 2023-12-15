#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>

class Thermistor {

  static constexpr uint8_t ADC_BITS = 10;

  static constexpr uint8_t SAMPLE_COUNT = 5;
  static constexpr uint8_t SAMPLE_PERIOD_MS = 2;
  static constexpr uint8_t VOLTAGE_STABLE_DELAY_MS = 2;

  // from Sensor Temperature Resistance Curves Reference Guide
  // for SC30F103VN thermistor
  static constexpr double A_COEFFICIENT = 3.3540154E-03;
  static constexpr double B_COEFFICIENT = 2.5627725E-04;
  static constexpr double C_COEFFICIENT = 2.0829210E-06;
  static constexpr double D_COEFFICIENT = 7.3003206E-08;

  String name;
  uint8_t sensePin;
  uint8_t powerPin;

  public:

  Thermistor(String name, uint8_t sensePin, uint8_t powerPin)
    : name(name), sensePin(sensePin), powerPin(powerPin) {};

  void begin();

  double temperatureFahrenheit();

  private:

  double readAbsoluteTemperature();
};

#endif // !THERMISTOR_H
