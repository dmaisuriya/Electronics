#include "Hardware/Hardware.h"
#include "Display/Menu.h"
#include "Display/VoltageGraph.h"
#include "ADC/ADC.h"

#include <U8g2lib.h>

#include <Arduino.h>

void Menu::MenuButton() {
    int reading = digitalRead(Hardware::MENU_PIN);

    // Detect a change in button state
    if (reading != lastButtonStateMenu) {
        lastDebounceTime = millis();
    }

    // Check whether the state has remained stable for 10ms
    if ((millis() - lastDebounceTime) > debounceDelay) {

        if (reading != buttonStateMenu) {
            buttonStateMenu = reading;

            // Only trigger once when the button is pressed
            if (buttonStateMenu == LOW) {
                Serial.println("Button clicked!");
                triggeredButtonMenu = 1;
            }
        }
    }

    lastButtonStateMenu = reading;
}

void Menu::MenuDisplay(VoltageGraph &display) {
    int potVal = analogRead(Hardware::MENU_SCROLL_PIN);

    if (triggeredButtonMenu == 1) {
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
        else if (activeMenu == 1 && potVal <= 1000) {
            voltagePage = 1;
            activeMenu = 0;
        }

        // Consume the button press AFTER processing it
        triggeredButtonMenu = 0;
    }

    // Draw the menu whenever it is active
    if (activeMenu == 1) {
        display.u8g2.clearBuffer();

        display.u8g2.setCursor(40, 5);
        display.u8g2.print("MODE SELECT:");

        display.u8g2.setCursor(30, 20);
        display.u8g2.print("Voltage Display");

        display.u8g2.setCursor(30, 30);
        display.u8g2.print("Current Display");

        display.u8g2.setCursor(30, 40);
        display.u8g2.print("Capacitance Measure");

        display.u8g2.setCursor(30, 50);
        display.u8g2.print("Resistance Measure");

        if (potVal <= 1000) {
            display.u8g2.drawCircle(selectPointX, selectPointY, selectPointR, U8G2_DRAW_ALL);
        }
        else if (potVal > 1000 && potVal <= 2000) {
            display.u8g2.drawCircle(selectPointX, selectPointY + 10, selectPointR, U8G2_DRAW_ALL);
        }
        else if (potVal > 2000 && potVal <= 3000) {
            display.u8g2.drawCircle(selectPointX, selectPointY + 20, selectPointR, U8G2_DRAW_ALL);
        }
        else if (potVal > 3000) {
            display.u8g2.drawCircle(selectPointX, selectPointY + 30, selectPointR, U8G2_DRAW_ALL);
        }
    }
}

void Menu::VoltageMode(VoltageGraph &display, ADC &adc) {
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

