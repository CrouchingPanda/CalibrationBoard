#include <Arduino.h>

#include "Transmitter.h"

void Transmitter::begin() {
  Serial1.begin(SERIAL_BAUD_RATE);
}

void Transmitter::setFirstThermistorTemperature(float temperature) {
  firstThermistorTemperature = temperature;
}

void Transmitter::setSecondThermistorTemperature(float temperature) {
  secondThermistorTemperature = temperature;
}

void Transmitter::transmit() {
  StaticJsonDocument<PAYLOAD_BYTES> dto;
  dto["firstThermistorTemperature"] = firstThermistorTemperature;
  dto["secondThermistorTemperature"] = secondThermistorTemperature;
  serializeJson(dto, Serial1);
  Serial1.flush();
}
