#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include<Servo.h>

const byte LCDcolumns = 16;
const byte LCDrows = 2;

Servo s_obj;
#define motor 3

#define button 4

#define w_sensor A0

// 0x27 is the default address. Is your address 0x3F - if so, change 0x27 to 0x3F
LiquidCrystal_I2C lcd(0x27, LCDcolumns, LCDrows);

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.home();
//  lcd.print("State:");

  pinMode(w_sensor, INPUT);

  pinMode(motor, OUTPUT);
  s_obj.attach(motor);
  pinMode(button, INPUT);
  s_obj.write(0);
  Serial.begin(9600);
}

void loop(){
  unsigned int w_level = analogRead(w_sensor), b_read = digitalRead(button);

  Serial.println(w_level);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Water level: ");
  
  if(b_read==HIGH)
  {
    lcd.println(w_level);
    s_obj.write(180);
    if(w_level>550)
    {
      lcd.setCursor(1,1);
      lcd.print("ENOUGH WATERING");
    }
  }
  else
    s_obj.write(0);
    
  
  delay(500);

}
