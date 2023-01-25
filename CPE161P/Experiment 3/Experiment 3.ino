//#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const byte LCDcolumns = 16;
const byte LCDrows = 2;

float temp_coeff = 0.48828125;

/*
 Multiplier for the sensor reading
  (5000mV-0mV)/(1024*10mV)
*/
#define temp_sensor A0
//const int temp_sensor = 0;

long long previous = 0, current;
  
// 0x27 is the default address. Is your address 0x3F - if so, change 0x27 to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);

void setup(){
  pinMode(temp_sensor, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.home();
  Serial.begin(9600);
  delay(1000); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(analogRead(temp_sensor)*temp_coeff);

}

/*
  Experiment 2: Weather Monitoring
    Objectives: 
      1. To demonstrate how a score board for a weather monitoring system works in real-time.
      2. To be able apply what you have learned in logic circuits and switching theory, microprocessors, and CPE160P.
      3. To be able to apply real-time embedded system using arduino kit.
    Materials and Conditions:
      Use the temperature sensor and the LCD. Measure the temperature using the sensor, and display in real-time the measured temperature. 
      The temperature value that will be displayed in the LCD shall be equal to the existing weather app's measurement. The measurement shall vary in real-time.
      Use the available materials you have to perform this experiment. Use the Arduino kit you used in the course CPE160P.
*/

void loop(){
  float temp_reading;
  current=millis();
  
  if(current-previous>=4000)
  {
    temp_reading = analogRead(temp_sensor)*temp_coeff;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temp_reading);
    previous=current;
  }

}



//void loop(){
//  float temp_reading;
//  current=millis();
//
//  
//  if(current-previous>=4000)
//  {
////    temp_reading = analogRead(temp_sensor)*temp_coeff;
//    temp_reading = (analogRead(temp_sensor)*0.05)+18;
//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("Temp: ");
//    lcd.print(temp_reading);
//    previous=current;
//  }
//  Serial.println((analogRead(temp_sensor)*0.05)+18); 
//
//}
