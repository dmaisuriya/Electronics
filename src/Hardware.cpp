#include "Hardware/Hardware.h"
#include <Arduino.h>
#include <U8g2lib.h>

void Hardware::PinSetup() {
    // setting pin modes for the ADC's SPI pins
    pinMode(DOUT_PIN, INPUT);
    pinMode(CS2_PIN, OUTPUT);
    pinMode(CLK2_PIN, OUTPUT);

    // initialising SPI's clock and CS pins
    digitalWrite(CS2_PIN, HIGH);
    digitalWrite(CLK2_PIN, LOW);
}