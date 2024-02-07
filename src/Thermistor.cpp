#include <math.h>

#include "Thermistor.h"

#include <Arduino.h>

constexpr uint8_t VOLTAGE_STABLE_DELAY_MS = 10;

// from Sensor Temperature Resistance Curves Reference Guide
// for SC30F103VN thermistor
constexpr double A_COEFFICIENT = 3.3540154E-03;
constexpr double B_COEFFICIENT = 2.5627725E-04;
constexpr double C_COEFFICIENT = 2.0829210E-06;
constexpr double D_COEFFICIENT = 7.3003206E-08;

void Thermistor::prepareForMeasurement() {
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, HIGH);
  isPowerPinHigh = true;
  preparingForMeasurementStartTimestamp = millis();
}

// we need to wait until the voltage on thermistor becomes stable
bool Thermistor::isReadyForMeasurement() {
  if (!isPowerPinHigh) return false;
  return millis() - preparingForMeasurementStartTimestamp >= VOLTAGE_STABLE_DELAY_MS;
}

void Thermistor::takeMeasurement(uint8_t adcResolutionBits) {
  analogRead(sensePin); // flush "stale" voltage out of ADC hardware

  double temperature = readAbsoluteTemperature(adcResolutionBits);
  
  digitalWrite(powerPin, LOW);

  double temperatureFahrenheit = (temperature - 273.15) * 9.0 / 5.0 + 32.0;
  lastTakenTemperatureFahrenheit = temperatureFahrenheit;
}

// from Sensor Temperature Resistance Curves Reference Guide
// for SC30F103VN thermistor; also see hardware layout
double Thermistor::readAbsoluteTemperature(uint8_t adcResolutionBits) {
  double adcDivisionCount = 1u << adcResolutionBits;
  double adcReading = analogRead(sensePin);
  double rtToR25 = 1.0 / ((adcDivisionCount / adcReading) - 1.0);
  double lnRtToR25 = log(rtToR25);
  return 1.0 / (
    A_COEFFICIENT +
    B_COEFFICIENT * lnRtToR25 +
    C_COEFFICIENT * pow(lnRtToR25, 2) +
    D_COEFFICIENT * pow(lnRtToR25, 3)
  );
}
