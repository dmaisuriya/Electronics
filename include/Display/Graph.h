#pragma once 

#include <Arduino.h>
#include <U8g2lib.h>

class Graph {
public:
    int graphStartX = 45;
    int graphStartY = 5;

    int graphEndX = 125;
    int graphEndY = 45;

    int lengthX = graphEndX - graphStartX;
    int lengthY = graphEndY - graphStartY;

    double maxVoltage = 0;
    double minVoltage = 0;
    double totalVoltage = 0;
    double squareTotalVoltage = 0;

    int dataBufferPixel[80];
    int counterY = -1;
    int counterX = -1;
    uint16_t dataBufferVoltage[80];

    static constexpr double V_REF = 5.0;
    static constexpr double ADC_CONV = V_REF/4096;

    void InitGraph (
        int graphStartX,
        int graphStartY, 
        int graphEndX,
        int graphEndY,
        int lengthX,
        int lengthY
    );

    U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2;
    Graph();

    void InitArray();

    void DrawGraph();

    void DisplayStats(const int& mappedValue, const uint16_t& valueADC);

};