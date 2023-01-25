#include <Servo.h>

#include <Key.h>
#include <Keypad.h>

#include <LiquidCrystal_I2C.h>
#define servoPin 3
#define buzzerPin A1
#define triggerPin A3
#define echoPin A2

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','0','-','-'},
  {'-','-','B','S'}
};

String inputPass = "------";
const String correctPass = "987654";
const int correctH = 0;
const int correctM = 1;

int startT = 0;
int current = 0;
int prev = 0;
const int convS = 1000;
int s = 0;
int mins = 0;
int hour = 0;
int keyNum = -1;
bool correct = 0;
bool onTime = 0;
bool near = 0;
int duration = 0;   


byte rowPins[ROWS] = {11,10,9,8};
byte colPins[COLS] = {7,6,5,4};

Keypad mykeypad = Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);
Servo myservo;
LiquidCrystal_I2C lcd(0x27,16,2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(servoPin);
  myservo.write(0);
  pinMode(buzzerPin,OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(1,0);

  digitalWrite(triggerPin,LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);

  startT = millis()/convS;
}

void loop() {
  // put your main code here, to run repeatedly:
  char inKey = mykeypad.getKey();
  current = (millis()/convS) - startT;
  digitalWrite(buzzerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
//  lcd.clear();
  Serial.println(inKey);
  if ((inKey)&&(inKey!= 'S')){
    if (inKey!= 'B'){
      keyNum++;
      if (keyNum > 6){
        keyNum = 0;
      }
      inputPass[keyNum] = inKey;
      //Serial.print(inputPass[keyNum]);
      //Serial.println();
      lcd.clear();
      lcd.print(inputPass);
    }
    
   if (inKey == 'B'){
      inputPass[keyNum] = '-';
      keyNum--;
      if (keyNum < 0){
        keyNum = 5;
      }
   }
  }

  String checkPass = inputPass;
  if ((checkPass == correctPass)&&(hour == correctH)&&(mins == correctM)){
    correct = 1;
    onTime = 1;
    }
  else
    correct = 0;

  if (prev < current)
  {
    s++;
    //Serial.println(s);
    prev = current;
  }

  if (s > 59)
  {
    mins++;
    s=0;
  }

  if (mins > 59)
  {
    hour++;
    mins = 0;
  }

  if (hour > 23)
  {
    hour = 0;
  }

  if (inKey == 'S'){

    if (duration <= 400){
      near = 1;
    }
    
    if (correct){
      if ((onTime)&&(near)){
      lcd.setCursor(0,1);
      lcd.print("ON TIME");
      lcd.setCursor(1,0);
      }

      if ((!onTime)&&(near)){
        lcd.setCursor(0,1);
      lcd.print("LATE");
      lcd.setCursor(1,0);
      digitalWrite(buzzerPin,HIGH);
      }
    }

    if ((!correct)||(!near)){
      lcd.setCursor(0,1);
      lcd.print("INCORRECT INPUT");
      lcd.setCursor(1,0);
      digitalWrite(buzzerPin,HIGH);
    }
  }
  
  Serial.println(onTime); 
  Serial.println(near); 
  Serial.println(inputPass);  
}
