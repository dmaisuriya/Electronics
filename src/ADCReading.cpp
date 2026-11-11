#include <Arduino.h>
#include "GPIOPins.h"

// define function that can store and return the 12-bit value from the ADC
uint16_t ReadADC(void) {
  uint16_t value = 0;

   // set low to start communication
  digitalWrite(Pins::CS2_PIN, LOW);

  // clock starts low
  digitalWrite(Pins::CLK2_PIN, LOW);

  // Generate 14 clocks.
  // Data appears after the falling edges.
  for (int clock = 1; clock <= 14; clock++)
  {
    // oscillating clock high and low sequence in the form a square waveform
    digitalWrite(Pins::CLK2_PIN, HIGH);
    delayMicroseconds(2);

    digitalWrite(Pins::CLK2_PIN, LOW);
    delayMicroseconds(2);

    // After falling edge 3, B11 is available
    if (clock >= 3)
    {
      int bit = digitalRead(Pins::DOUT_PIN);

      value = (value << 1) | bit;
    }
  }

  // set CS high to end communication
  digitalWrite(Pins::CS2_PIN, HIGH);

  return value;
}