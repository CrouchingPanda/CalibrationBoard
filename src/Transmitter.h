#include <Arduino.h>

#include <SerialTransfer.h>

#include <InterboardSerial.h>

class Transmitter {

  SerialTransfer transmitter;

  public:

  Transmitter() : transmitter(SerialTransfer()) {};

  void begin();

  void send(const DTO& dto);
};