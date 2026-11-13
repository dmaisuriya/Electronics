#include <Arduino.h>
#include <U8g2lib.h>

#include "Display/Graph.h"
#include "Hardware/Hardware.h"
#include "ADC/ADC.h"

Graph display;
Hardware hardware;

void setup(void) {
  Serial.begin(115200);
  
  hardware.PinSetup();
  display.InitArray();

  // start up the display
  display.u8g2.begin();
  display.u8g2.setFont(u8g2_font_04b_03_tr);
}

void loop(void) {
  ADC ADC;

  // call function to map the ADC values
  ADC.MapADCtoGraph(display.graphEndY, display.graphStartY);

  // clears the screen
  display.u8g2.clearBuffer();
  // call function to draw the graph axis
  display.InitGraph (
    display.graphStartX,
    display.graphStartY, 
    display.graphEndX, 
    display.graphEndY, 
    display.lengthX, 
    display.lengthY
    );

  display.DisplayStats(ADC.mappedValue, ADC.valueADC);
  display.DrawGraph();
  display.u8g2.sendBuffer();
}
