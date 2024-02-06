#include "Transmitter.h"

#include <Arduino.h>

#include <SerialTransfer.h>
#include <InterboardSerial.h>

void Transmitter::begin() {
  Serial1.begin(SERIAL_BAUD_RATE);
  transmitter.begin(Serial1);
}

void Transmitter::send(const DTO& dto) {
  transmitter.sendDatum(dto);
  Serial1.flush();
}
