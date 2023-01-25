#include<Stepper.h>
#include<Servo.h>

//step motor pins
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5

//servo motor
#define servo 13
Servo s;
int pos=90;

//proximity sensor pins
#define echo 9
#define trig 8
long duration;
int distance;

//rotation is 512 for 90-degree rotation
int rotation = 650, dt = 50, motor_speed = 50;
Stepper motor(rotation, IN1, IN3, IN2, IN4);

bool presser_closed;

void setup() {
  // put your setup code here, to run once:
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  
  
  motor.setSpeed(motor_speed);
  Serial.begin(9600);

  delay(2500);
  
  pinMode(servo, OUTPUT);
  s.attach(servo);
  s.write(0);
//  motor.step(-200);
//  delay(dt);  
   
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = 0;
  presser_closed=false;
  distance = read_distance();
//  s.write(100);
//  delay(100);
  Serial.println(distance);
  if(!presser_closed)
  {
    if(distance<10)
    {
    motor.step(rotation);
    delay(dt);  
    presser_closed=true;
    motor.step(-rotation);
    delay(dt);  
    delay(1000);
    distance = read_distance();
    if(distance<10)
      s.write(90);     
    }
  }
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
