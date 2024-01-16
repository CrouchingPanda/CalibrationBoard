#ifndef LED_H
#define LED_H

#include <Arduino.h>

#include <jled.h>

class LED {

  JLed led;

  public:

  LED(uint8_t pin) : led(JLed(pin)) {};

  void blink();

  void on();
};

#endif // !LED_H
