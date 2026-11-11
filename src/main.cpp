#include <Arduino.h>
#include <U8g2lib.h>
#include "GPIOPins.h"
#include "GraphVars.h"
#include "MapADC.h"
#include "DrawGraph.h"
#include <cmath>

// declaring the array to have a history of the ADC values, and stores one sample per pixel (80 pixels total which is length of x-axis)
int dataBufferPixel[80];
double dataBufferVoltage[80];

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
    dataBufferPixel[i] = plotValues.graphEndY;
    dataBufferVoltage[i] = 0.0;
  }

  // start up the display
  u8g2.begin();
  u8g2.setFont(u8g2_font_04b_03_tr);

}

void loop(void) {
  // initialise the graph plotting values
  graphPlots initPlot;
  graphStats stats;

  // call function to map the ADC values
  ADC adcReading = MapADCtoGraph(initPlot);

  // loop through the array of ADC values and shift everything to the right by 1
  for (int i = initPlot.lengthX - 1; i > 0; i--) {
    dataBufferPixel[i] = dataBufferPixel[i-1];
    dataBufferVoltage[i] = dataBufferVoltage[i-1];
  }

  // replace the first value of the array with the most current reading and now the graph scrolls from left-right
  dataBufferPixel[0] = adcReading.mappedValue;
  dataBufferVoltage[0] = adcReading.valueADC;

  for (int i = 1; i < 80; i++) {
    if (dataBufferVoltage[i] >= stats.maxVoltage) {
      stats.maxVoltage = dataBufferVoltage[i];
    }
    if (dataBufferVoltage[i] <= stats.minVoltage) {
      stats.minVoltage = dataBufferVoltage[i];
    }
    stats.totalVoltage += dataBufferVoltage[i];
    stats.squareTotalVoltage += dataBufferVoltage[i]*dataBufferVoltage[i];
  }

  // clears the screen
  u8g2.clearBuffer();
  // call function to draw the graph axis
  InitGraph(initPlot);

  // go through all 80 pixels on the x-axis and connect adjacent points together to display a proper line graph
  for (int i = 0; i < initPlot.lengthX-1; i++) {
    u8g2.drawLine(i + initPlot.graphStartX, dataBufferPixel[i], i + initPlot.graphStartX + 1, dataBufferPixel[i+1]);
  }

  u8g2.setCursor(initPlot.graphStartX - 45, initPlot.graphStartY + 10);
  u8g2.printf("MAX: %.2fV", stats.maxVoltage*voltageVars::ADC_CONV);

  u8g2.setCursor(initPlot.graphStartX - 45, initPlot.graphStartY + 20);
  u8g2.printf("MIN: %.2fV", stats.minVoltage*voltageVars::ADC_CONV);

  u8g2.setCursor(initPlot.graphStartX - 45, initPlot.graphStartY + 30);
  u8g2.printf("AVG: %.2fV", (stats.totalVoltage/80)*voltageVars::ADC_CONV);

  u8g2.setCursor(initPlot.graphStartX - 45, initPlot.graphStartY + 40);
  u8g2.printf("RMS: %.2fV", sqrt(stats.squareTotalVoltage/80)*voltageVars::ADC_CONV);

  u8g2.sendBuffer();
}
