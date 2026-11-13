#include "ADC/ADC.h"

// function to get the ADC reading and mapped value
void ADC::MapADCtoGraph(int graphEndY, int graphStartY) {
  // caling the function to get the 12-bit ADC reading
  valueADC = ADC::ReadADC();

  // mapping this value in the correct proportion of the length of the y axis
  mappedValue = map(valueADC, 0, 4095, graphEndY, graphStartY);
}