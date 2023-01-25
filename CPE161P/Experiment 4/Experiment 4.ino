#include<Keypad.h>
#include<Servo.h>

const int rows = 4, cols = 4;

char keys[rows][cols] = 
{
  {'A','B','C','D'},
  {'E','F','G','H'},
  {'I','J','K','L'},
  {'M','N','O','P'}  
};

byte rowpins[rows] = {5,4,3,2}, colpins[cols] = {6,7,8,9}; 

Keypad k_obj = Keypad(makeKeymap(keys), rowpins, colpins, rows, cols);


//step motor pins
//#define IN1 10
//#define IN2 11
//#define IN3 12
//#define IN4 13

//rotation is 512 for 90-degree rotation
//int rotation = 500, dt = 50, motor_speed = 50;
//Stepper motor(rotation, IN1, IN3, IN2, IN4);

#define red A0
#define green A1
#define blue A2

#define buzzer A3
#define servo_pin 10
Servo s;

void rgb(int r, int g, int b);
void off_all();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
//  pinMode(buzzer, OUTPUT);
  
  s.attach(servo_pin);
  s.write(0);
//  motor.setSpeed(motor_speed);
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = k_obj.getKey();
  long long previous, current;    
  int x = 0;

  
  Serial.println(key);
  switch(key)
  {
    case 'C':
    case 'A':
      previous=millis();
      while(true)
      {
        key=k_obj.getKey();
        if(key=='B')
          break;
        while((current-previous!=1000)&&(x==0))
        {
          current=millis();
          off_all();
          rgb(255,0,0);
//          if(k_obj.getKey()=='B')
//            break;
        }
        key=k_obj.getKey();
        previous=current;
        x++;
        if(key=='B')
          break;
          
        key=k_obj.getKey();
        if(key=='B')
          break;
        while((current-previous!=1000)&&(x==1))
        {
          current=millis();
          off_all();
          rgb(0,255,0);
//          if(k_obj.getKey()=='B')
//            break;
        }
        key=k_obj.getKey();
        previous=current;
        x++;
        if(key=='B')
          break;
          
        key=k_obj.getKey();
        if(key=='B')
          break;
        while((current-previous!=1000)&&(x==2))
        {
          current=millis();
          off_all();
          rgb(0,0,255);
//          if(k_obj.getKey()=='B')
//            break;
        }
        key=k_obj.getKey();
        previous=current;
        x=0;
        if(key=='B')
          break;
      }
      break;
    case 'B':
      break;
    case 'D':
      off_all();
      break;
    case 'G':
    case 'E':
      while(true)
      {
         delay(100);
         if(k_obj.getKey()=='F')
           break;
         tone(buzzer,100);
         delay(100);
         if(k_obj.getKey()=='F')
           break;
         noTone(buzzer);
         if(k_obj.getKey()=='F')
           break;
         Serial.println(k_obj.getKey());
      }
      break;
    case 'F':
      break;
    case 'H':
      noTone(buzzer);
      break;
    case 'K':
    case 'I':
      int servo_pos=0;
      while(true)
      {
        servo_pos+=30;
        if(k_obj.getKey()=='J')
          break;
        s.write(servo_pos);
        delay(150);
        if(k_obj.getKey()=='J')
          break;
        if(servo_pos>=180)
          servo_pos=0;
        if(k_obj.getKey()=='J')
          break;
      }
      break;
    case 'J':
      break;
    case 'L':
      s.write(0);
      break;
    case 'M':
      break;
    case 'N':
      break;
    case 'O':
      break;
    case 'P':
      break;
  }
}

void rgb(int r = 0, int g = 0, int b = 0)
{
  analogWrite(red, r);
  analogWrite(green, g);
  analogWrite(blue, b);
}

void off_all()
{
  analogWrite(red, 0);
  analogWrite(green, 0);
  analogWrite(blue, 0);  
}
