#include "LED.h"

#include <stdint.h>

#include <Arduino.h>

#include <jled.h>

constexpr uint8_t BLINK_ON_TIME_MS = 10;
constexpr uint8_t BLINK_OFF_TIME_MS = 1;

constexpr uint8_t ON_BRIGHTNESS = 50;

void LED::blink() {
  led.Blink(BLINK_ON_TIME_MS, BLINK_OFF_TIME_MS);
  while (led.Update());
}

void LED::on() {
  led.On(ON_BRIGHTNESS).Update();
}
