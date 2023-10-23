#ifndef THERMISTOR_METER_H
#define THERMISTOR_METER_H

constexpr static bool THERMISTOR_METER_STUB = true;

#include <Arduino.h>

#include <Adc.h>

class ThermistorMeter {

  static constexpr float SERIES_RESISTANCE = 10000.0;

  // Steinhart - Hart equation coefficients for USP10982 thermistor
  // calculated with 0°C, 25°C and 60°C points per RT table
  static constexpr float A_COEFFICIENT = 1.127598029e-3;
  static constexpr float B_COEFFICIENT = 2.343604016e-4;
  static constexpr float C_COEFFICIENT = 8.687814791e-8;

  uint8_t sensePin;
  uint8_t powerPin;

  Adc* adc;

  public:

  ThermistorMeter(uint8_t sensePin, uint8_t powerPin)
    : sensePin(sensePin), powerPin(powerPin) {};

  void begin();

  float temperatureFarengheit();
};

#endif // !THERMISTOR_METER_H
