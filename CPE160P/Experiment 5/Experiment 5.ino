#include<Stepper.h>
#include<Servo.h>

//proximity sensor pins
#define echo A2
#define trig A1
long duration;
int distance;

//step motor pins
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

//photoresistor
#define ldr A0

//servo motor
#define servo 3
Servo s;
int pos=90;

//4-Digit SSD
#define D1 0
#define D2 0
#define D3 A3
#define D4 A4
#define a 8
#define b 9
#define c 10
#define d 11
#define e 12
#define f 13
#define g A5

//counter
int in_counter = 0, in_max = 10;

//rotation is 512 for 90-degree rotation
int rotation = 500, dt = 50, motor_speed = 50;
Stepper motor(rotation, IN1, IN3, IN2, IN4);

//write functions
void write_D1(int disp=0);
void write_D2(int disp=0);
void write_D3(int disp=0);
void write_D4(int disp=0);
void write_num(int num = 0);

void setup() {
  // put your setup code here, to run once:

  
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(a, OUTPUT);;
  pinMode(b, OUTPUT);;
  pinMode(c, OUTPUT);;
  pinMode(d, OUTPUT);;
  pinMode(e, OUTPUT);;
  pinMode(f, OUTPUT);;
  pinMode(g, OUTPUT);
  
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  
  pinMode(ldr, INPUT);

  pinMode(servo, OUTPUT);
  s.attach(servo);
  s.write(0);
  
  motor.setSpeed(motor_speed);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(D3, HIGH);
  write_D4(in_counter);
  // put your main code here, to run repeatedly:
  int p_res = analogRead(ldr);
//  Serial.println(in_counter);

    //for photoresistor
  if(p_res<50)
  {
    delay(500);
    s.write(90);
    while(p_res<50)
    {
      p_res = analogRead(ldr);
      if(p_res>50)
      {
        delay(500);
        s.write(0);
        in_counter--;
        break;
      }
    }
  }
  else
  {
    delay(500);
    s.write(0);
  }
  //for entrance
  Serial.println(in_counter);
  distance = read_distance();
  if(distance<15&&in_counter==in_max)
    distance=15;
    
  if(distance<15)
  {
    motor.step(rotation);
    delay(dt);    
    delay(1000);
    while(distance<15)
    {
      distance = read_distance();

      if(distance>15)
      {
        motor.step(-(rotation));
        delay(dt);
        in_counter++;
        break;        
      }
    }
  }
  else
  {
    motor.step(0);
    delay(dt);
  }
  
//  Serial.println(in_counter);
//  Serial.println(p_res);
//  if(p_res<=300)
//    Serial.println("DARK");
//  else
//    Serial.println("BRIGHT");

}

int read_distance()
{
    digitalWrite(trig, LOW);
    delay(2);

    digitalWrite(trig, HIGH);
    delay(10);
    digitalWrite(trig, LOW);
       
   duration = pulseIn(echo, HIGH);
   distance = duration*0.034/2;

   return distance;
}

//Format for write function per digit:
/*
  - set digits not to be written to high which will be complemented in a 4-digit 7-segment display
  - write the disp parameter which is 0 by default
  - insert a delay
  - set all segments to low
*/
//write function for D1
void write_D1(int disp=0)
{
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  write_num(disp);

  delay(5);
  set_all_low();
}

//write function for D2
void write_D2(int disp=0)
{
  digitalWrite(D1, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);

  write_num(disp);

  delay(5);
  set_all_low();
}

//write function for D3
void write_D3(int disp=0)
{
  digitalWrite(D2, HIGH);
  digitalWrite(D1, HIGH);
  digitalWrite(D4, HIGH);

  write_num(disp);

  delay(5);
  set_all_low();
}

//write function for D4
void write_D4(int disp=0)
{
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D1, HIGH);

   write_num(disp);

  delay(5);
  set_all_low();
}

//close all of the current digit
void off_all()
{
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);
}

//set all digits to LOW
void set_all_low()
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  
}


//write function on current digit
/*
  format:
  - close all first
  - enter switch statement
*/
void write_num(int num = 0)
{
  off_all();
  switch(num)
  {
    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
//      digitalWrite(g, HIGH);
      break;
    case 1:
//      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
//      digitalWrite(d, HIGH);
//      digitalWrite(e, HIGH);
//      digitalWrite(f, HIGH);
//      digitalWrite(g, HIGH);
      break;
    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
//      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
//      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
//      digitalWrite(e, HIGH);
//      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 4:
//      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
//      digitalWrite(d, HIGH);
//      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 5:
      digitalWrite(a, HIGH);
//      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
//      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 6:
      digitalWrite(a, HIGH);
//      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
//      digitalWrite(d, HIGH);
//      digitalWrite(e, HIGH);
//      digitalWrite(f, HIGH);
//      digitalWrite(g, HIGH);
      break;
    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;  
    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
//      digitalWrite(d, HIGH);
//      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;  
  }
}
