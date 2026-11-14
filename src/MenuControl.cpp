#include "Hardware/Hardware.h"
#include "Display/Menu.h"
#include "Display/Graph.h"
#include "ADC/ADC.h"

#include <U8g2lib.h>

#include <Arduino.h>

void Menu::MenuButton() {
    int reading = digitalRead(Hardware::MENU_PIN);

    // Detect a change in button state
    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    // Check whether the state has remained stable for 10ms
    if ((millis() - lastDebounceTime) > debounceDelay) {

        if (reading != buttonState) {
            buttonState = reading;

            // Only trigger once when the button is pressed
            if (buttonState == LOW) {
                Serial.println("Button clicked!");
                triggeredButton = 1;
            }
        }
    }

    lastButtonState = reading;
}

void Menu::MenuDisplay(Graph &display) {

    if (triggeredButton == 1) {

        int potVal = analogRead(Hardware::MENU_SCROLL_PIN);

        // If we're on the voltage page, return to the menu
        if (voltagePage == 1) {
            voltagePage = 0;
            activeMenu = 1;
        }

        // If we're on starting blank screen, open the menu
        else if (activeMenu == 0) {
            activeMenu = 1;
        }

        // If we're on the menu, select voltage display
        else if (activeMenu == 1 && potVal >= 4095) {
            voltagePage = 1;
            activeMenu = 0;
        }

        // Consume the button press AFTER processing it
        triggeredButton = 0;
    }

    // Draw the menu whenever it is active
    if (activeMenu == 1) {
        display.u8g2.clearBuffer();

        display.u8g2.setCursor(20, 20);
        display.u8g2.print("MENU!");

        display.u8g2.setCursor(20, 40);
        display.u8g2.print("Voltage Display?");
    }
}

void Menu::VoltageMode(Graph &display, ADC &adc) {
    display.u8g2.clearBuffer();

    adc.MapADCtoGraph(display.graphEndY, display.graphStartY);
  
    // call function to draw the graph axis
    display.InitGraph (
      display.graphStartX,
      display.graphStartY, 
      display.graphEndX, 
      display.graphEndY, 
      display.lengthX, 
      display.lengthY
    );

    display.DisplayStats(adc.mappedValue, adc.valueADC);
    display.DrawGraph();
}

