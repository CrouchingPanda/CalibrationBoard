#include <math.h>

#include "Thermistor.h"

#include <Arduino.h>

void Thermistor::begin() {
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);
}

double Thermistor::temperatureFahrenheit() {
  digitalWrite(powerPin, HIGH);
  delay(VOLTAGE_STABLE_DELAY_MS);
  
  analogRead(sensePin); // flush ADC

  double sum = 0.0;
  for (uint8_t i = 0; i < SAMPLE_COUNT; i++) {
    delay(SAMPLE_PERIOD_MS);
    sum += readAbsoluteTemperature();
  }

  digitalWrite(powerPin, LOW);

  double averageTemperature = sum / SAMPLE_COUNT;
  double temperatureFahrenheit = (averageTemperature - 273.15) * 9.0 / 5.0 + 32.0;
  
  Serial.print("Thermistor \"");
  Serial.print(name); 
  Serial.print("\": ");
  Serial.print(temperatureFahrenheit);
  Serial.println('F');
  
  return temperatureFahrenheit;
}

// from Sensor Temperature Resistance Curves Reference Guide
// for SC30F103VN thermistor 
double Thermistor::readAbsoluteTemperature() {
  static double adcDivisionCount = 1u << ADC_BITS;
  double rtToR25 = 1.0 / ((adcDivisionCount / analogRead(sensePin)) - 1.0);
  double lnRtToR25 = log(rtToR25);
  return 1.0 / (
    A_COEFFICIENT +
    B_COEFFICIENT * lnRtToR25 +
    C_COEFFICIENT * pow(lnRtToR25, 2) +
    D_COEFFICIENT * pow(lnRtToR25, 3)
  );
}
