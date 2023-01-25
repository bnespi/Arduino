#define smoke A0
#define led A1
#define buzzer A2

void setup() {
  // put your setup code here, to run once:
  pinMode(smoke, INPUT);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  while(!Serial){}

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  int s_reading = analogRead(smoke);
  Serial.println(s_reading);

  if(s_reading>350)
  {
    digitalWrite(led, HIGH);
    tone(buzzer, 1000);
    delay(500);
    noTone(buzzer);
    digitalWrite(led, LOW);
    delay(500);
  } 
//  delay(100);
}
