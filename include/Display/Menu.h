#pragma once

#include <Arduino.h>
#include "Display/VoltageGraph.h"
#include "ADC/ADC.h"

class Menu {
public:
    unsigned long lastDebounceTime = 0;
    const unsigned long debounceDelay = 10;

    int buttonStateMenu = HIGH;
    int lastButtonStateMenu = HIGH;

    int triggeredButtonMenu = 0;
    int activeMenu = 0;
    int voltagePage = 0;

    static constexpr int selectPointX = 25;
    static constexpr int selectPointY = 18;
    static constexpr int selectPointR = 1;

    void MenuButton();
    void MenuDisplay(VoltageGraph &display);
    void VoltageMode(VoltageGraph &display, ADC &adc);
};
