#include <U8g2lib.h>
#include <cmath>

#include "Hardware/Hardware.h"
#include "Display/Graph.h"
#include "ADC/ADC.h"


Graph::Graph()
  : u8g2 (
    U8G2_R0, 
    Hardware::CLK_PIN, 
    Hardware::SDA_PIN, 
    Hardware::CS_PIN, 
    Hardware::DC_PIN, 
    Hardware::RES_PIN
    )
{}

// function to initialise an empty graph on the display
void Graph::InitGraph(int graphStartX, int graphStartY, int graphEndX, int graphEndY, int lengthX, int lengthY) {
  counterY = -1;
  counterX = -1;

  // calculating step size for scale on each axis
  int incrementY = 5;
  int incrementX = 10;
  int stepY = lengthY/incrementY;
  int stepX = lengthX/incrementX;

  // drawing the x and y axis lines
  u8g2.drawVLine(graphStartX,graphStartY,lengthY);
  u8g2.drawHLine(graphStartX+1,graphEndY,lengthX);

  // drawing the incremented scale lines on the y axis
  for (int i = graphStartY; i <= graphEndY; i += stepY) {
    u8g2.drawLine(graphStartX-1, i, graphStartX-3, i);
    for (int j = graphStartX; j <= graphEndX; j++) {
      if (j % 2 == 0) {
        u8g2.drawPixel(j, i);
      }
    }
    counterY++;
  }

  // drawing the incremented scale lines on the x axis
  for (int i = graphStartX; i <= graphEndX; i += stepX) {
    u8g2.drawLine(i, graphEndY+1, i, graphEndY+3);
    for (int j = graphEndY; j >= graphStartY; j--) {
      if (j % 2 == 0) {
        u8g2.drawPixel(i, j);
      }
    }
    counterX++;
  }
}

void Graph::InitArray() {
  // initialise all values to be initially at the bottom of the graph
  for (int i = 0; i < 80; i++) {
    dataBufferPixel[i] = graphEndY;
    dataBufferVoltage[i] = 0;
  }
}

void Graph::DrawGraph() {
  // go through all 80 pixels on the x-axis and connect adjacent points together to display a proper line graph
  for (int i = 0; i < lengthX-1; i++) {
    u8g2.drawLine(i + graphStartX, dataBufferPixel[i], i + graphStartX + 1, dataBufferPixel[i+1]);
  }
}

void Graph::DisplayStats(const int& mappedValue, const uint16_t& valueADC) {

  maxVoltage = dataBufferVoltage[0];
  minVoltage = dataBufferVoltage[0];
  totalVoltage = 0;
  squareTotalVoltage = 0;

  for (int i = lengthX - 1; i > 0; i--) {
    dataBufferPixel[i] = dataBufferPixel[i-1];
    dataBufferVoltage[i] = dataBufferVoltage[i-1];
  }

  // replace the first value of the array with the most current reading and now the graph scrolls from left-right
  dataBufferPixel[0] = mappedValue;
  dataBufferVoltage[0] = valueADC;

  // finding max and min values 
  for (int i = 1; i < 80; i++) {
    if (dataBufferVoltage[i] >= maxVoltage) {
      maxVoltage = dataBufferVoltage[i];
    }
    if (dataBufferVoltage[i] <= minVoltage) {
      minVoltage = dataBufferVoltage[i];
    }
    totalVoltage += dataBufferVoltage[i];
    squareTotalVoltage += dataBufferVoltage[i]*dataBufferVoltage[i];
  }

  u8g2.setCursor(graphStartX, graphEndY + 15);
  u8g2.printf("%.2fV/div Y-Axis", V_REF/counterY);

  u8g2.setCursor(graphStartX - 45, graphStartY + 10);
  u8g2.printf("MAX: %.2fV", maxVoltage*ADC_CONV);

  u8g2.setCursor(graphStartX - 45, graphStartY + 20);
  u8g2.printf("MIN: %.2fV", minVoltage*ADC_CONV);

  u8g2.setCursor(graphStartX - 45, graphStartY + 30);
  u8g2.printf("AVG: %.2fV", (totalVoltage/80)*ADC_CONV);

  u8g2.setCursor(graphStartX - 45, graphStartY + 40);
  u8g2.printf("RMS: %.2fV", sqrt(squareTotalVoltage/80)*ADC_CONV);

  u8g2.setCursor(graphStartX - 45, graphStartY + 50);
  u8g2.printf("VOLT: %.2fV", dataBufferVoltage[0]*ADC_CONV);  
}
