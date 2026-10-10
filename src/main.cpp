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

const double ADC_CONV = 3.3/4096;

U8G2_SH1106_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, CLK_PIN, SDA_PIN, CS_PIN, DC_PIN, RES_PIN);

uint16_t readADC(void)
{
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

void initGraph() {
  int graphDrawEndY = 50;
  int graphDrawEndX = 100;

  int graphDrawStartX = 20;
  int graphDrawStartY = 10;

  int incrementY = 5;
  int stepY = (graphDrawEndY-graphDrawStartY)/incrementY;

  int incrementX = 5;
  int stepX = (graphDrawEndX-graphDrawStartX)/incrementX;

  u8g2.drawVLine(graphDrawStartX,graphDrawStartY,graphDrawEndY-graphDrawStartY);
  u8g2.drawHLine(graphDrawStartX,graphDrawEndY,graphDrawEndX-graphDrawStartX);

  for (int i = graphDrawStartY; i <= graphDrawEndY; i += stepY) {
    u8g2.drawLine(graphDrawStartX-1, i, graphDrawStartX-3, i);
  }

  // fix this
  for (int i = graphDrawStartX; i <= graphDrawEndX; i += stepX) {
    u8g2.drawLine(i, graphDrawEndY-1, i, graphDrawEndY-3);
  }

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


void loop(void) { 
  uint16_t value = readADC();

  u8g2.clearBuffer();
  initGraph();
  //u8g2.setFont(u8g2_font_ncenB14_tr);
  //u8g2.setCursor(32,32);
  //u8g2.print(ADC_CONV*value);
  //u8g2.print("V");
  u8g2.sendBuffer();

}