#include "GraphVars.h"
#include <U8g2lib.h>
#include "DrawGraph.h"
#include "GPIOPins.h"

U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(
  U8G2_R0, 
  Pins::CLK_PIN, 
  Pins::SDA_PIN, 
  Pins::CS_PIN, 
  Pins::DC_PIN, 
  Pins::RES_PIN
);

// function to initialise an empty graph on the display
void InitGraph(graphPlots &initPlot) {
  // finding X and Y lengths of the graph
  initPlot.lengthX = initPlot.graphEndX-initPlot.graphStartX;
  initPlot.lengthY = initPlot.graphEndY-initPlot.graphStartY;

  // calculating step size for scale on each axis
  int incrementY = 5;
  int incrementX = 10;
  int stepY = initPlot.lengthY/incrementY;
  int stepX = initPlot.lengthX/incrementX;

  // drawing the x and y axis lines
  u8g2.drawVLine(initPlot.graphStartX,initPlot.graphStartY,initPlot.lengthY);
  u8g2.drawHLine(initPlot.graphStartX+1,initPlot.graphEndY,initPlot.lengthX);

  int counterY = -1;
  int counterX = -1;

  // drawing the incremented scale lines on the y axis
  for (int i = initPlot.graphStartY; i <= initPlot.graphEndY; i += stepY) {
    u8g2.drawLine(initPlot.graphStartX-1, i, initPlot.graphStartX-3, i);
    for (int j = initPlot.graphStartX; j <= initPlot.graphEndX; j++) {
      if (j % 2 == 0) {
        u8g2.drawPixel(j, i);
      }
    }
    counterY++;
  }

  // drawing the incremented scale lines on the x axis
  for (int i = initPlot.graphStartX; i <= initPlot.graphEndX; i += stepX) {
    u8g2.drawLine(i, initPlot.graphEndY+1, i, initPlot.graphEndY+3);
    for (int j = initPlot.graphEndY; j >= initPlot.graphStartY; j--) {
      if (j % 2 == 0) {
        u8g2.drawPixel(i, j);
      }
    }
    counterX++;
  }

  u8g2.setCursor(initPlot.graphStartX - 5, initPlot.graphEndY + 15);
  u8g2.printf("%.2fV/div (On Y-Axis)", voltageVars::V_REF/counterY);

}
