#ifndef ANALOG_READER_H
#define ANALOG_READER_H

#include <Arduino.h>

#include "Thermistor.h"

class AnalogReader {

  static constexpr uint8_t MAX_THERMISTOR_COUNT = 2;
  
  Thermistor* thermistors[MAX_THERMISTOR_COUNT]{};
  
  int8_t lastAddedThermistorIndex = -1;

  public:

  void begin();

  void takeMeasurements();
  
  AnalogReader& addThermistor(Thermistor& thermistor);
};

#endif // !ANALOG_READER_H
