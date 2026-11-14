#include "Display/VoltageScale.h"
#include "Hardware/Hardware.h"

void VoltageScale::VScaleButton() {
  int reading = digitalRead(Hardware::VSCALE_PIN);

  // Detect a change in button state
  if (reading != lastButtonStateScale) {
    lastDebounceTime = millis();
  }

  // Check whether the state has remained stable for 10ms
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonStateScale) {
      buttonStateScale = reading;

      // Only trigger once when the button is pressed
      if (buttonStateScale == LOW) {
        Serial.println("Button clicked!");
        triggeredButtonScale = 1;
      }
    }
  }
  lastButtonStateScale = reading;
}

void VoltageScale::VScaleSettings(Menu &menuControls, VoltageGraph &display) {
  if (triggeredButtonScale == 1 && menuControls.voltagePage == 1 && menuControls.activeMenu == 0) {
    display.u8g2.clearBuffer();
    display.u8g2.setCursor(50, 25);
    display.u8g2.print("IT WORKS!!!");
    // fix this when im back 
  }
}