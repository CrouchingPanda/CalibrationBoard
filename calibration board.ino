#include <LowPower.h>

#include "src/Transmitter.h"
#include "src/ThermistorMeter.h"

auto firstMeter = ThermistorMeter(A4, 7);
auto secondMeter = ThermistorMeter(A5, 9);
auto transmitter = Transmitter();

void setup() {
  firstMeter.begin();
  secondMeter.begin();
  transmitter.begin();

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  transmitter.setFirstThermistorTemperature(firstMeter.temperatureFarengheit());
  transmitter.setSecondThermistorTemperature(secondMeter.temperatureFarengheit());
  transmitter.transmit();

  LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
}
