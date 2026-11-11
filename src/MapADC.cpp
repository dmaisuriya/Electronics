#include "ADCReading.h"
#include "GraphVars.h"

// function to get the ADC reading and mapped value
ADC MapADCtoGraph(graphPlots &initPlot) {
  // caling the function to get the 12-bit ADC reading
  //unsigned long t1 = micros();
  uint16_t value = ReadADC();
  //unsigned long t2 = micros();

  // mapping this value in the correct proportion of the length of the y axis
  int mapY = map(value, 0, 4095, initPlot.graphEndY, initPlot.graphStartY);

  // store the variables here in the adcReading data type
  ADC adcReading = {value, mapY};

  // return both the 12-bit value and mapped value
  return adcReading;
}