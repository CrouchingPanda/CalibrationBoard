#include "AnalogReader.h"

#include <stdint.h>
#include <stdlib.h>

#include <Arduino.h>

constexpr eAnalogReference REFERENCE_VOLTAGE = AR_VDD4; // VDD
constexpr uint8_t RESOLUTION_BITS = 14;
constexpr uint8_t SAMPLING_PERIOD_MICROSECONDS = 5;
constexpr uint16_t OVERSAMPLING_COUNT = 256;

void AnalogReader::begin() {
  analogReference(REFERENCE_VOLTAGE);
  analogSampleTime(SAMPLING_PERIOD_MICROSECONDS);
  analogReadResolution(RESOLUTION_BITS);
  analogOversampling(OVERSAMPLING_COUNT);
}

void AnalogReader::takeMeasurements() {
  if (lastAddedThermistorIndex < 0) return;

  analogCalibrateOffset();

  for (size_t i = 0; i <= lastAddedThermistorIndex; i++) {
    thermistors[i]->prepareForMeasurement();
  }

  for (size_t i = 0; i <= lastAddedThermistorIndex; i++) {
    while (!thermistors[i]->isReadyForMeasurement());
  }

  for (size_t i = 0; i <= lastAddedThermistorIndex; i++) {
    thermistors[i]->takeMeasurement(RESOLUTION_BITS);
  }
}

AnalogReader& AnalogReader::addThermistor(Thermistor& thermistor) {
  if (lastAddedThermistorIndex == MAX_THERMISTOR_COUNT - 1) return *this;
  
  lastAddedThermistorIndex++;
  thermistors[lastAddedThermistorIndex] = &thermistor;
  return *this;
}
