#pragma once

#include <Arduino.h>

class ADC {
public:
    uint16_t valueADC;
    int mappedValue;

    uint16_t ReadADC();
    void MapADCtoGraph(int graphEndY, int graphStartY);
};