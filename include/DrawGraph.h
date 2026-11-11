#pragma once

#include "GraphVars.h"
#include <U8g2lib.h>

namespace voltageVars {
    constexpr double V_REF = 5.0;
    constexpr double ADC_CONV = V_REF/4096;
}

extern U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2;

void InitGraph(graphPlots &initPlot);