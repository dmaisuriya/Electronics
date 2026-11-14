#pragma once

#include <Arduino.h>
#include "Display/Graph.h"
#include "ADC/ADC.h"

class Menu {
public:
    unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 10;

    int buttonState = HIGH;
    int lastButtonState = HIGH;
    int triggeredButton = 0;
    int activeMenu = 0;
    int voltagePage = 0;

    void MenuButton();
    void MenuDisplay(Graph &display);
    void VoltageMode(Graph &display, ADC &adc);
};
