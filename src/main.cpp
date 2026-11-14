#include <Arduino.h>
#include <U8g2lib.h>

#include "Display/VoltageGraph.h"
#include "Hardware/Hardware.h"
#include "ADC/ADC.h"
#include "Display/Menu.h"
#include "Display/VoltageScale.h"

// initialising all my custom classes that each represents a different task of the project
Hardware hardware;
Menu menuControls;
ADC adc;
VoltageScale vScale;
VoltageGraph display;

void setup(void) {
  Serial.begin(115200);
  
  hardware.PinSetup(); // initialise the GPIO pins
  display.InitArray(); // initialise the array that will store the data points for graphing voltage

  // start up the display
  display.u8g2.begin();
  display.u8g2.setFont(u8g2_font_04b_03_tr);
}

void loop(void) {
  menuControls.MenuButton(); // checks if the button for opening the menu is pressed
  menuControls.MenuDisplay(display); // displays the menu if the button is pressed

  if (menuControls.voltagePage == 1) { 
    menuControls.VoltageMode(display, adc); // if voltage page is requested to show, it displays it
  }

  vScale.VScaleButton();
  vScale.VScaleSettings(menuControls, display);

  display.u8g2.sendBuffer(); // sends buffer to OLED and actually displays whatever is prompted

}
