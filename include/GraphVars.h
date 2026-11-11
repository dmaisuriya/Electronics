#pragma once

#include <Arduino.h>

// custom data type to store all the significant graph drawing coordinates
struct graphPlots {
  int graphStartX = 45;
  int graphStartY = 5;

  int graphEndX = 125;
  int graphEndY = 45;

  int lengthX;
  int lengthY;
};

// custom data type to store all graph stats
struct graphStats {
  double maxVoltage = 0;
  double minVoltage = 0;
  double totalVoltage = 0;
  double squareTotalVoltage = 0;
};

// custom data type to store ADC readings and its mapped value for the display
struct ADC {
  uint16_t valueADC;
  int mappedValue;
};