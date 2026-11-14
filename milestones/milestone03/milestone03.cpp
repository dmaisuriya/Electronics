#include <Arduino.h>
#include <U8g2lib.h>

#include "Display/Graph.h"
#include "Hardware/Hardware.h"
#include "ADC/ADC.h"
#include "Display/Menu.h"

Graph display;
Hardware hardware;
Menu menuControls;
ADC adc;

void setup(void) {
  Serial.begin(115200);
  
  hardware.PinSetup();
  display.InitArray();

  // start up the display
  display.u8g2.begin();
  display.u8g2.setFont(u8g2_font_04b_03_tr);

}

void loop(void) {

  int potVal = analogRead(Hardware::MENU_SCROLL_PIN);
  Serial.printf("%d\n", potVal);

  menuControls.MenuButton();
  menuControls.MenuDisplay(display);

  if (menuControls.voltagePage == 1) {
    menuControls.VoltageMode(display, adc);
  }

  display.u8g2.sendBuffer();
}

