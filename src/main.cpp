#include <Arduino.h>
#include <iostream>
#include <U8g2lib.h>
#include "GPIOPins.h"
#include "GraphVars.h"
#include "MapADC.h"
#include "DrawGraph.h"

// declaring the array to have a history of the ADC values, and stores one sample per pixel (80 pixels total which is length of x-axis)
uint16_t dataBuffer[80];

void setup(void) {
  Serial.begin(115200);

  graphPlots plotValues;

  // setting pin modes for the ADC's SPI pins
  pinMode(Pins::DOUT_PIN, INPUT);
  pinMode(Pins::CS2_PIN, OUTPUT);
  pinMode(Pins::CLK2_PIN, OUTPUT);

  // initialising SPI's clock and CS pins
  digitalWrite(Pins::CS2_PIN, HIGH);
  digitalWrite(Pins::CLK2_PIN, LOW);

  // initialise all values to be initially at the bottom of the graph
  for (int i = 0; i < 80; i++) {
    dataBuffer[i] = plotValues.graphEndY;
  }

  // start up the display
  u8g2.begin();
  u8g2.setFont(u8g2_font_04b_03_tr);

}

void loop(void) {
  // initialise the graph plotting values
  graphPlots initPlot;

  // call function to map the ADC values
  ADC adcReading = MapADCtoGraph(initPlot);

  // loop through the array of ADC values and shift everything to the right by 1
  for (int i = initPlot.lengthX - 1; i > 0; i--) {
    dataBuffer[i] = dataBuffer[i-1];
  }
  // replace the first value of the array with the most current reading and now the graph scrolls from left-right
  dataBuffer[0] = adcReading.mappedValue;

  // clears the screen
  u8g2.clearBuffer();
  // call function to draw the graph axis
  InitGraph(initPlot);

  // go through all 80 pixels on the x-axis and connect adjacent points together to display a proper line graph
  for (int i = 0; i < initPlot.lengthX-1; i++) {
    u8g2.drawLine(i + initPlot.graphStartX, dataBuffer[i], i + initPlot.graphStartX + 1, dataBuffer[i+1]);
  }

  // setting the font and location to write the voltage value on the y-axis
  u8g2.setCursor(initPlot.graphStartX - 25, adcReading.mappedValue);

  // print the actual voltage value
  u8g2.print(voltageVars::ADC_CONV*adcReading.valueADC);
  u8g2.print("V");

  u8g2.sendBuffer();
}
