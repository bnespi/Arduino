#include<Stepper.h>

long duration;
int distance;
#define echo 2
#define trig 3

#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

//rotation is 512 for 90-degree rotation
int rotation = 500, dt = 50, motor_speed = 60;
Stepper motor(rotation, IN1, IN3, IN2, IN4);

#define backward_button 8
#define forward_button 9


void setup() {
  // put your setup code here, to run once:
  motor.setSpeed(motor_speed);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(backward_button, INPUT);
  pinMode(forward_button, INPUT);
  
  delay(1000);
  Serial.begin(9600);
}

int read_distance()
{
//   digitalWrite(trig, LOW);
//   delay(2);

   digitalWrite(trig, HIGH);
   delay(10);
   digitalWrite(trig, LOW);
       
   duration = pulseIn(echo, HIGH);
//   distance = duration*0.034/2;
   distance = duration*0.017;

   return distance;
}


void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(forward_button)==HIGH)
  {
    while(true)
    {
      motor.step(1000);
      if(read_distance()<50)
      {
        motor.step(0);
        break;
      }
    }
  }
  if(digitalRead(backward_button)==HIGH)
  {
    while(true)
    {
      motor.step(-1000);
      if(read_distance()<50)
      {
        motor.step(0);
        break;
      }
    }
  }
}
