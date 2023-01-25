//4-Digit SSD
#define D1 12
#define D2 11
#define D3 10
#define D4 9
#define a 8
#define b 7
#define c 6
#define d 5
#define e 4
#define f 3
#define g 2

//IR Sensor
#define p_res A0
//Buzzer
#define buzz 13

//Buttons
#define b1 A1
#define b2 A2

//LEDs
#define red A3
#define yellow A4
#define green A5

void setup() {
  //Outputs
  //4-Digit SSD
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  
  //Buzzer
  
  //LEDs
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);

  //Inputs
  //IR Sensor
  pinMode(p_res, INPUT);
  
  //Buttons
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);

  Serial.begin(9600);
}

  /*
  - Demonstrate the normal operation of the traffic lights. Use three different LEDs for the stop(RED), ready(YELLOW), and go(GREEN).  
  - Switches (2) will be used to pre-empt the nornal operation of the traffic lights. 
  - If the first switch is pressed, 15 seconds will be deducted from the normal counting before it reaches the GO signal. 
  - If the second switch is pressed, 30 seconds will be added from the normal counting before it reacheds the STOP signal.  
  - Two Seven-segment display (SSD) will display the counting before the go signal . 
  - The system will count 60 (incrementation) seconds before the GO signal, 60(decrementation) seconds again before the RED signal, 
     during the 30th seconds, the READY signal will lit. 
  - A sensor will be used to sense cars that beats the RED signal, and an alarm will ring.
  */
  
  /*
  STOPLIGHT FOR PEOPLE
  GO is for people to walk
  STOP is for people to stand
  By default, the timer will have 60 seconds for the STOP and GO.
  3 seconds for the WAIT.
  Infrared sensor will be used to determine if a car will beat the GO signal.
  A buzzer will be rang if this happens.
  
  If b1 is pressed, the STOP time will be deducted 15 seconds.
  If b2 is pressed, the GO time will be increased 30 seconds.

  */
void write_SSD(int x, int y);
  

void loop() {
  write_SSD(2,0);
  green_light();
  
  yellow_light();
  
  write_SSD(2,0);
  red_light();

}

void yellow_light()
{
  int timer = 3, current, previous=0;
  digitalWrite(yellow, HIGH);
  while(timer>0)
  {
    current = millis();
    //print on ssd
    write_SSD(3,timer);

    
    //decrement accordingly
    if(current-previous==1000)
    {
      timer--;
      previous=current;
    }
  }
  digitalWrite(yellow, LOW);
}

void red_light()
{
  int tens = 6, ones = 0, b1reading, current, previous=0;
  digitalWrite(red,HIGH);
  while(tens>=0)
  {
    current=millis();
    b1reading=digitalRead(b1);

    //print on ssd
    write_SSD(3,ones);
    write_SSD(2,tens);
  
    //check if either buttons are pressed
  
    //only for red light
    b1reading=digitalRead(b1);
    if(b1reading)
    {
      tens--;
      ones-=5;
      delay(100);
    }
    //only for green light
    //  if(digitalRead(b2)==HIGH)
    //    tens+=3;

    //decrement accordingly
    if(current-previous==1000)
    {
//      Serial.println(ones);
      ones--;
      previous=current;
    }
    if(ones<0)
    {
      tens--;
      ones=9;
    }

    b1reading=digitalRead(b1);
  }
  digitalWrite(red,LOW);
}

void green_light()
{
  int tens = 6, ones = 0, b2reading, p_res_reading, current, previous=0;
  digitalWrite(green,HIGH);
  while(tens>=0)
  {
    current=millis();
    p_res_reading=analogRead(p_res);
    b2reading=digitalRead(b2);
    
    //print on ssd
    write_SSD(3,ones);
    write_SSD(2,tens);
  
    //check if either buttons are pressed
  
    //only for red light
//    if(digitalRead(b1)==HIGH)
//    {
//      tens--;
//      ones-=5;
//    }
    //only for green light
    b2reading=digitalRead(b2);
    if(b2reading==HIGH)
    {
      tens+=3;
      delay(100);
    }
    if(p_res_reading<100)
    {
      tone(buzz, 100);
      delay(10);
      noTone(buzz);      
    }
    //decrement accordingly
    if(current-previous==1000)
    {
      Serial.println(previous);
      ones--;
      previous=current;      
    }
    if(ones<0)
    {
      tens--;
      ones=9;
    }
    if(tens>6)
      tens=6;
      
    b2reading=digitalRead(b2); 
    p_res_reading=analogRead(p_res);   
  }  
  digitalWrite(green,LOW);
}

void write_SSD(int x=0, int y=0)
{
  on_allD();
  switch(x)
  {
    case 1:
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);  
      break;
    case 2:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, HIGH);  
      break;
    case 3:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, LOW);
      digitalWrite(D4, HIGH);  
      break;
    case 4:
      digitalWrite(D1, HIGH);
      digitalWrite(D2, HIGH);
      digitalWrite(D3, HIGH);
      digitalWrite(D4, LOW);  
      break;
  }

  off_all();
  switch(y)
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
  off_all();
  off_allD();
}

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

void on_all()
{
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH); 
}

void on_allD()
{
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);  
}

void off_allD()
{
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);  
}