#include <Arduino.h>
#include <iostream>
#include <cstring>
#include <U8g2lib.h>

// intialising all the GPIO pins for the OLED SPI display
const int CLK_PIN = 22;
const int SDA_PIN = 21;
const int RES_PIN = 19;
const int DC_PIN = 18;
const int CS_PIN = 23;

// intialising all the GPIO pins for the ADC's SPI communication
const int CS2_PIN = 27;
const int DOUT_PIN = 13;
const int CLK2_PIN = 14;

// arithmetic to convert the ADC's 12 bit reading into the voltage
const double ADC_CONV = 3.3/4096;

// initialising constructor to use the u8g2 lib for the SPI display
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, CLK_PIN, SDA_PIN, CS_PIN, DC_PIN, RES_PIN);


void setup(void) {
  Serial.begin(115200);

  // setting pin modes for the ADC's SPI pins
  pinMode(DOUT_PIN, INPUT);
  pinMode(CS2_PIN, OUTPUT);
  pinMode(CLK2_PIN, OUTPUT);

  // initialising SPI's clock and CS pins
  digitalWrite(CS2_PIN, HIGH);
  digitalWrite(CLK2_PIN, LOW);

  // start up the display
  u8g2.begin();

}

// define function that can store and return the 12-bit value from the ADC
uint16_t readADC(void)
{
  uint16_t value = 0;

  // set low to start communication
  digitalWrite(CS2_PIN, LOW);

  // clock starts low
  digitalWrite(CLK2_PIN, LOW);

  // Generate 14 clocks.
  // Data appears after the falling edges.
  for (int clock = 1; clock <= 14; clock++)
  {
    // oscillating clock high and low sequence in the form a square waveform
    digitalWrite(CLK2_PIN, HIGH);
    delayMicroseconds(2);

    digitalWrite(CLK2_PIN, LOW);
    delayMicroseconds(2);

    // After falling edge 3, B11 is available
    if (clock >= 3)
    {
      int bit = digitalRead(DOUT_PIN);

      value = (value << 1) | bit;
    }
  }

  // set CS high to end communication
  digitalWrite(CS2_PIN, HIGH);

  // return 12-bit ADC reading
  return value;
}

void loop(void) { 
  // run the function to get ADC reading
  uint16_t value = readADC();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_tr);
  u8g2.setCursor(0,16);

  // print the voltage value on the screen
  u8g2.print(ADC_CONV*value);
  u8g2.print("V");
  u8g2.sendBuffer();

}
