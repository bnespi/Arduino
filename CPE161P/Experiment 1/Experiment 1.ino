//buttons
#define l_team_inc 2
#define l_team_dec 3
#define r_team_inc 4
#define r_team_dec 5

//4-DIGIT SSD
#define D1 6
#define D2 7
#define D3 8
#define D4 9
#define a 10
#define b 11
#define c 12
#define d 13
#define e A2
#define f A3
#define g A4

//photoresistor
#define r_p_res A0
#define l_p_res A1

int l_score = 0, r_score = 0;
  
//write functions
void write_D1(int disp=0);
void write_D2(int disp=0);
void write_D3(int disp=0);
void write_D4(int disp=0);
void write_num(int num = 0);

void setup() {
  // put your setup code here, to run once:
  pinMode(l_team_inc, INPUT);
  pinMode(l_team_dec, INPUT);
  pinMode(r_team_inc, INPUT);
  pinMode(r_team_dec, INPUT);

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
  
  pinMode(r_p_res, INPUT);
  pinMode(l_p_res, INPUT);

  write_D2(l_score);
  write_D4(r_score);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print("Left Team Increase:");
//  Serial.println(digitalRead(l_team_inc));
//  Serial.println("Right Team Increase:");
//  Serial.println(digitalRead(r_team_inc));
//  Serial.println("Left Team Decrease:");
//  Serial.println(digitalRead(l_team_dec));
//  Serial.println("Right Team Decrease:");
//  Serial.println(digitalRead(r_team_dec));
//  Serial.println("Right Photoresistor:");
//  Serial.println(analogRead(r_p_res));
//  Serial.println("Left Photoresistor:");
//  Serial.println(analogRead(l_p_res));

  //photoresistor read
//  int l_pres = analogRead(l_p_res), r_pres = analogRead(r_p_res);

//  write_D1(x);
//  write_D2(y);
//  write_D3(x);
//  write_D4(y);
  
//  Serial.println(analogRead(l_p_res));


  if(digitalRead(l_team_inc)!=LOW)
  {
    l_score++;
    delay(125);
  }
  
  if(digitalRead(l_team_dec)!=LOW)
  {
    l_score--;
    delay(125);
  }
  
  if(digitalRead(r_team_inc)!=LOW)
  {
    r_score++;
    delay(125);
  }
  
  if(digitalRead(r_team_dec)!=LOW)
  {
    r_score--;
    delay(125);
  }
  
  if(analogRead(l_p_res)<1020)
  {
    l_score+=2;
    delay(125);
  }
  
  if(analogRead(r_p_res)<1020)
  {
    r_score+=2;
    delay(125);
  }


//  set_all_low();
  //ones digits
  write_D2(l_score%10);
  write_D4(r_score%10);

  //tens digits
  write_D1(l_score/10);
  write_D3(r_score/10); 

  if(l_score>99)
    l_score=0;
  if(r_score>99)
    r_score=0;
  
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

//set all digits to HIGH
void set_all_high()
{
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
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
