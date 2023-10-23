#include <math.h>

#include "ThermistorMeter.h"

#include <Arduino.h>

void ThermistorMeter::begin() {
  if (THERMISTOR_METER_STUB) return;

  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);

  adc = new Adc(sensePin);
  adc->begin();
}

float ThermistorMeter::temperatureFarengheit() {
  if (THERMISTOR_METER_STUB) {
    static float lastOutput = 95.0;
    if (lastOutput < 95.0) {
      lastOutput += 1.99;
    } else {
      lastOutput -= 1.99;
    }
    return lastOutput;
  }

  digitalWrite(powerPin, HIGH);

  float thermistorResistance = SERIES_RESISTANCE / ((1 / adc->reading()) - 1);
  float absoluteTemperature = 1.0 / (
    A_COEFFICIENT +
    B_COEFFICIENT * log(thermistorResistance) +
    C_COEFFICIENT * pow(log(thermistorResistance), 3)
    );
  float farengheitTemperature = ((absoluteTemperature - 273.15) * 9.0) / 5.0 + 32.0;

  digitalWrite(powerPin, LOW);

  return farengheitTemperature;
}