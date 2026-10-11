#include <Arduino.h>
#include <iostream>
#include <cstring>
#include <U8g2lib.h>

const int CLK_PIN = 22;
const int SDA_PIN = 21;
const int RES_PIN = 19;
const int DC_PIN = 18;
const int CS_PIN = 23;

const int CS2_PIN = 27;
const int DOUT_PIN = 13;
const int CLK2_PIN = 14;

const double ADC_CONV = 5.0/4096;

U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, CLK_PIN, SDA_PIN, CS_PIN, DC_PIN, RES_PIN);

struct graphPlots {
  int graphStartX = 30;
  int graphStartY = 10;

  int graphEndX = 110;
  int graphEndY = 50;

  int lengthX;
  int lengthY;
};

struct ADC {
  uint16_t valueADC;
  int mappedValue;
};

uint16_t ReadADC(void) {
  uint16_t value = 0;

  digitalWrite(CS2_PIN, LOW);
  digitalWrite(CLK2_PIN, LOW);

  // Generate 14 clocks.
  // Data appears after the falling edges.
  for (int clock = 1; clock <= 14; clock++)
  {
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

  digitalWrite(CS2_PIN, HIGH);

  return value;
}

void InitGraph(graphPlots &initPlot) {
  initPlot.lengthX = initPlot.graphEndX-initPlot.graphStartX;
  initPlot.lengthY = initPlot.graphEndY-initPlot.graphStartY;

  int increment = 5;
  int step = initPlot.lengthY/increment;

  u8g2.drawVLine(initPlot.graphStartX,initPlot.graphStartY,initPlot.lengthY);
  u8g2.drawHLine(initPlot.graphStartX+1,initPlot.graphEndY,initPlot.lengthX);

  for (int i = initPlot.graphStartY; i <= initPlot.graphEndY; i += step) {
    u8g2.drawLine(initPlot.graphStartX-1, i, initPlot.graphStartX-3, i);
  }

  for (int i = initPlot.graphStartX; i <= initPlot.graphEndX; i += step) {
    u8g2.drawLine(i, initPlot.graphEndY+1, i, initPlot.graphEndY+3);
  }
}

ADC MapADCtoGraph(graphPlots &initPlot) {
  uint16_t value = ReadADC();
  int mapY = map(value, 0, 4095, initPlot.graphEndY, initPlot.graphStartY);

  ADC adcReading = {value, mapY};

  return adcReading;
}

void setup(void) {
  Serial.begin(115200);
  
  pinMode(DOUT_PIN, INPUT);
  pinMode(CS2_PIN, OUTPUT);
  pinMode(CLK2_PIN, OUTPUT);

  digitalWrite(CS2_PIN, HIGH);
  digitalWrite(CLK2_PIN, LOW);

  u8g2.begin();

}

uint16_t dataBuffer[80] = {0};

void loop(void) { 
  graphPlots initPlot;

  ADC adcReading = MapADCtoGraph(initPlot);

  for (int i = 1; i < initPlot.lengthX; i++) {
    dataBuffer[i-1] = dataBuffer[i];
  }
  dataBuffer[initPlot.lengthX - 1] = adcReading.mappedValue; 

  u8g2.clearBuffer();
  InitGraph(initPlot);

  for (int i = 0; i < initPlot.lengthX-1; i++) {
    u8g2.drawLine(i + initPlot.graphStartX, dataBuffer[i], i + initPlot.graphStartX + 1, dataBuffer[i+1]);
  } 

  u8g2.setFont(u8g2_font_04b_03_tr);
  u8g2.setCursor(initPlot.graphStartX - 25, adcReading.mappedValue);

  u8g2.print(ADC_CONV*adcReading.valueADC);
  u8g2.print("V");

  u8g2.sendBuffer();

}