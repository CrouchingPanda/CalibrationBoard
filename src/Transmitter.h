#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <Arduino.h>

#include <ArduinoJson.h>

class Transmitter {

  static constexpr uint16_t SERIAL_BAUD_RATE = 9600;

  static constexpr uint8_t PAYLOAD_BYTES = JSON_OBJECT_SIZE(2);

  float firstThermistorTemperature = 0.0;
  float secondThermistorTemperature = 0.0;

  public:

  void begin();

  void setFirstThermistorTemperature(float temperature);
  
  void setSecondThermistorTemperature(float temperature);

  void transmit();
};

#endif // !TRANSMITTER_H