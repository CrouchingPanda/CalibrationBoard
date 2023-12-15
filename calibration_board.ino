#include <LowPower.h>
#include <InterboardSerial.h>
#include <SerialTransfer.h>
#include <jled.h>

#include "src/Thermistor.h"

constexpr uint16_t TRANSMISSION_PERIOD_MS = 1000;

constexpr uint8_t TRANSMIT_LED_PIN = 10;
constexpr uint8_t POWER_LED_PIN = 11;

auto transmitter = SerialTransfer();

auto firstMeter = Thermistor("Primary", A4, 7);
auto secondMeter = Thermistor("Secondary", A5, 9);

auto transmitLed = JLed(TRANSMIT_LED_PIN).Blink(10, 1);

void setup() {
  JLed(POWER_LED_PIN).Set(50).Update();

  firstMeter.begin();
  secondMeter.begin();

  Serial1.begin(SERIAL_BAUD_RATE);
  transmitter.begin(Serial1);
}

static uint32_t lastTransmissionTimestampMs = 0;

void loop() {
  transmitLed.Update();

  if (millis() - lastTransmissionTimestampMs < TRANSMISSION_PERIOD_MS) return; 

  DTO dto;
  dto.primaryThermistorTemperatureFahrenheit = firstMeter.temperatureFahrenheit();
  dto.secondaryThermistorTemperatureFahrenheit = secondMeter.temperatureFahrenheit();
  
  transmitter.sendDatum(dto);
  Serial1.flush();
  lastTransmissionTimestampMs = millis();
  
  transmitLed.Reset();

  LowPower.idle(
    SLEEP_1S, 
    ADC_OFF, 
    TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, 
    TIMER0_ON, // left ON to drive PWM of LEDs
    SPI_OFF, USART1_OFF, TWI_OFF, USB_OFF);
}
