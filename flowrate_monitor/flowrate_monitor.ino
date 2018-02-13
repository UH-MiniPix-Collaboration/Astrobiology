#include "sma.h"
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Define pins and variables
const int flowPin = A0;
const String unit = " mL/min";
float flowRate = 0;
String previousRate;

//Returns flowrate value that will be filtered through SMA
float getFlowRate()
{
  return mapf(analogRead(flowPin), 0, 1023, 0, 50);
}

//Redefines map() function to report fractions
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

SMAFilter sma0(2, getFlowRate);

void setup() {
  Serial.begin(9600);

  //Initialize LCD
  lcd.begin(16,2);
  lcd.print("Flowrate");
  lcd.setCursor(0,1);
  lcd.print("Monitor");
  delay(1000);
  lcd.clear();
}

void loop() {
  //LCD Output
  lcd.setCursor(0,0);
  lcd.print("Prev:" + previousRate);
  lcd.setCursor(0,1);
  flowRate =  sma0.getFilteredSample();
  lcd.print("Curr:" + (flowRate + unit));

  //Serial Monitor output
  Serial.print("Flow Rate: ");
  Serial.print(flowRate);
  Serial.println(unit);
  
  previousRate = flowRate + unit;
  delay(500);
}
