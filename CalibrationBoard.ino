#include "src/AnalogReader.h"
#include "src/LED.h"
#include "src/Transmitter.h"

constexpr uint16_t TRANSMISSION_PERIOD_MS = 1000;

auto transmitter = Transmitter();

auto powerLed = LED(11);
auto transmitLed = LED(10);

auto primaryThermistor = Thermistor().setSensePin(A4).setPowerPin(7);
auto secondaryThermistor = Thermistor().setSensePin(A5).setPowerPin(9);

auto analogReader = AnalogReader()
  .addThermistor(primaryThermistor)
  .addThermistor(secondaryThermistor);

void setup() {
  powerLed.on();
  transmitter.begin();
  analogReader.begin();
}

void loop() {
  analogReader.takeMeasurements();

  DTO dto;
  dto.primaryThermistorTemperatureFahrenheit = primaryThermistor.temperatureFahrenheit();
  dto.secondaryThermistorTemperatureFahrenheit = secondaryThermistor.temperatureFahrenheit();
  
  transmitter.send(dto);
  transmitLed.blink();

  delay(TRANSMISSION_PERIOD_MS);
}