#include <dht.h>
#include<Servo.h>

#define dht_pin A0
#define sound_sensor A1
#define servo A2

dht DHT;
Servo s;
bool c;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(sound_sensor, INPUT);
  pinMode(servo, OUTPUT);
  s.attach(servo);
  delay(1500);
  s.write(0);
  c=0;
}

void loop() {
  // put your main code here, to run repeatedly:

  //for sound sensor
  int s_intensity = analogRead(sound_sensor), pos=180;
  //Serial.print(s_intensity);
  //Serial.print(" ");
  //Serial.println(DHT.humidity);

  //for humidity sensor
  DHT.read11(dht_pin);
  
  if(s_intensity>360&&DHT.humidity>=90)
    c=1;
  
  while(c)
  {
    delay(500);
    s.write(pos++);
    if(s_intensity<360&&DHT.humidity>=80)
      break;
  }

  
//  Serial.println(DHT.humidity);
}
