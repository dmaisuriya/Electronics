#include <Arduino.h>
#include <iostream>
#include <cstring>
#include <U8g2lib.h>

// intialising all the GPIO pins for the OLED SPI display
const int CLK_PIN = 22;
const int SDA_PIN = 21;
const int RES_PIN = 19;
const int DC_PIN = 18;
const int CS_PIN = 23;

// intialising all the GPIO pins for the ADC's SPI communication
const int CS2_PIN = 27;
const int DOUT_PIN = 13;
const int CLK2_PIN = 14;

// arithmetic to convert the ADC's 12 bit reading into the voltage
const double ADC_CONV = 5.0/4096;

// initialising constructor to use the u8g2 lib for the SPI display
U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, CLK_PIN, SDA_PIN, CS_PIN, DC_PIN, RES_PIN);

// custom data type to store all the significant graph drawing coordinates
struct graphPlots {
  int graphStartX = 30;
  int graphStartY = 10;

  int graphEndX = 110;
  int graphEndY = 50;

  int lengthX;
  int lengthY;
};

// custom data type to store ADC readings and its mapped value for the display
struct ADC {
  uint16_t valueADC;
  int mappedValue;
};

// define function that can store and return the 12-bit value from the ADC
uint16_t ReadADC(void) {
  uint16_t value = 0;

   // set low to start communication
  digitalWrite(CS2_PIN, LOW);

  // clock starts low
  digitalWrite(CLK2_PIN, LOW);

  // Generate 14 clocks.
  // Data appears after the falling edges.
  for (int clock = 1; clock <= 14; clock++)
  {
    // oscillating clock high and low sequence in the form a square waveform
    digitalWrite(CLK2_PIN, HIGH);
    delayMicroseconds(2);

    digitalWrite(CLK2_PIN, LOW);
    delayMicroseconds(2);

    // After falling edge 3, B11 is available
    if (clock >= 3)
    {
      int bit = digitalRead(DOUT_PIN);

      value = (value << 1) | bit;
    }
  }

  // set CS high to end communication
  digitalWrite(CS2_PIN, HIGH);

  return value;
}

// function to initialise an empty graph on the display
void InitGraph(graphPlots &initPlot) {
  // finding X and Y lengths of the graph
  initPlot.lengthX = initPlot.graphEndX-initPlot.graphStartX;
  initPlot.lengthY = initPlot.graphEndY-initPlot.graphStartY;

  // calculating step size for scale on each axis
  int increment = 5;
  int step = initPlot.lengthY/increment;

  // drawing the x and y axis lines
  u8g2.drawVLine(initPlot.graphStartX,initPlot.graphStartY,initPlot.lengthY);
  u8g2.drawHLine(initPlot.graphStartX+1,initPlot.graphEndY,initPlot.lengthX);

  // drawing the incremented scale lines on the y axis
  for (int i = initPlot.graphStartY; i <= initPlot.graphEndY; i += step) {
    u8g2.drawLine(initPlot.graphStartX-1, i, initPlot.graphStartX-3, i);
  }

  // drawing the incremented scale lines on the x axis
  for (int i = initPlot.graphStartX; i <= initPlot.graphEndX; i += step) {
    u8g2.drawLine(i, initPlot.graphEndY+1, i, initPlot.graphEndY+3);
  }
}

// function to get the ADC reading and mapped value
ADC MapADCtoGraph(graphPlots &initPlot) {
  // caling the function to get the 12-bit ADC reading
  uint16_t value = ReadADC();
  // mapping this value in the correct proportion of the length of the y axis
  int mapY = map(value, 0, 4095, initPlot.graphEndY, initPlot.graphStartY);

  // store the variables here in the adcReading data type
  ADC adcReading = {value, mapY};

  // return both the 12-bit value and mapped value
  return adcReading;
}

void setup(void) {
  Serial.begin(115200);

  // setting pin modes for the ADC's SPI pins
  pinMode(DOUT_PIN, INPUT);
  pinMode(CS2_PIN, OUTPUT);
  pinMode(CLK2_PIN, OUTPUT);

  // initialising SPI's clock and CS pins
  digitalWrite(CS2_PIN, HIGH);
  digitalWrite(CLK2_PIN, LOW);

  // start up the display
  u8g2.begin();

}

// initialising the array to have a history of the ADC values, and stores one sample per pixel (80 pixels total which is length of x-axis)
uint16_t dataBuffer[80] = {0};

void loop(void) { 
  // initialise the graph plotting values
  graphPlots initPlot;

  // call function to map the ADC values
  ADC adcReading = MapADCtoGraph(initPlot);

  // loop through the array of ADC values and shift everything to the right by 1
  for (int i = initPlot.lengthX - 1; i >= 0; i--) {
    dataBuffer[i] = dataBuffer[i-1];
  }
  // replace the first value of the array with the most current reading and now the graph scrolls from left-right
  dataBuffer[0] = adcReading.mappedValue;

  // clears the screen
  u8g2.clearBuffer();
  // call function to draw the graph axis
  InitGraph(initPlot);

  // go through all 80 pixels on the x-axis and connect adjacent points together to display a proper line graph
  for (int i = 0; i < initPlot.lengthX-1; i++) {
    u8g2.drawLine(i + initPlot.graphStartX, dataBuffer[i], i + initPlot.graphStartX + 1, dataBuffer[i+1]);
  } 

  // setting the font and location to write the voltage value on the y-axis
  u8g2.setFont(u8g2_font_04b_03_tr);
  u8g2.setCursor(initPlot.graphStartX - 25, adcReading.mappedValue);

  // print the actual voltage value
  u8g2.print(ADC_CONV*adcReading.valueADC);
  u8g2.print("V");

  u8g2.sendBuffer();

}
