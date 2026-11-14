#pragma once

#include "Display/Menu.h"

class VoltageScale {
public:
    int buttonStateScale = HIGH;
    int lastButtonStateScale = HIGH;
    int triggeredButtonScale = 0;

    const unsigned long debounceDelay = 10;
    unsigned long lastDebounceTime = 0;

    void VScaleButton();
    void VScaleSettings(Menu &menuControls, VoltageGraph &display);
};