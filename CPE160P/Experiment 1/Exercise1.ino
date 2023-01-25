
#define RED1 13
#define RED2 12
#define RED3 11
#define GREEN1 8
#define GREEN2 7
#define GREEN3 6
#define YELLOW1 10
#define YELLOW2 9
#define BUTTON1 5
#define BUTTON2 4
#define BUTTON3 3
#define BUTTON4 2

int state1 = LOW,state2 = LOW,state3 = LOW,state4 = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);
  pinMode(RED2, OUTPUT);
  pinMode(YELLOW1, OUTPUT);
  pinMode(YELLOW2, OUTPUT);
  pinMode(GREEN2, OUTPUT);
  pinMode(RED3, OUTPUT);
  pinMode(GREEN3, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  state1 = digitalRead(BUTTON1);
  state2 = digitalRead(BUTTON2);
  state3 = digitalRead(BUTTON3);
  state4 = digitalRead(BUTTON4);  
  
  
  
  if(state1 != LOW)
  {
    song1();
    
  }
  if(state2 != LOW)
  {
    delay(700);
    song2();

  }
  if(state3 != LOW)
  {
    song3();

  }
  if(state4 != LOW)
  {
    delay(1000);
    song4();
    
  }
}

void song1()
{
  //Selena Gomez & The Scene - Love You Like A Love Song
  //https://www.youtube.com/watch?v=EgT_us6AsDg
  pattern1();
  chorus();
  off_all();
  pattern1();

}

void off_all()
{
  digitalWrite(RED1, LOW);
  digitalWrite(RED2, LOW);
  digitalWrite(RED3, LOW);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(YELLOW2, LOW);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW); 
}

void blink_led(double t)
{
  delay(t);
  digitalWrite(RED1, LOW);
  digitalWrite(RED2, LOW);
  digitalWrite(RED3, LOW);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(YELLOW2, LOW);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW); 
  delay(t);
  digitalWrite(RED1, HIGH);
  digitalWrite(RED2, HIGH);
  digitalWrite(RED3, HIGH);
  digitalWrite(YELLOW1, HIGH);
  digitalWrite(YELLOW2, HIGH);
  digitalWrite(GREEN1, HIGH);
  digitalWrite(GREEN2, HIGH);
  digitalWrite(GREEN3, HIGH);  
}


void chorus()
{
  for(int x = 0; x < 65; x++)
  {
    blink_led(250);
  }
}

void pattern1()
{
  for(int x = 0; x<15; x++)
  {
    red(550);
    green(550);
  }
  transition(150);
}

void transition(double t)
{
  digitalWrite(YELLOW1, HIGH);
  delay(t);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(YELLOW2, HIGH);
  delay(t);
  digitalWrite(YELLOW2, LOW);
}

void strum_red()
{
  digitalWrite(RED1, HIGH);
  delay(50);
  digitalWrite(RED1, LOW);
  digitalWrite(RED2, HIGH);
  delay(50);
  digitalWrite(RED2, LOW);
  digitalWrite(RED3, HIGH);
  delay(50);
  digitalWrite(RED3, LOW);
}

void strum_yellow()
{
  digitalWrite(YELLOW1, HIGH);
  delay(50);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(YELLOW2, HIGH);
  delay(50);
  digitalWrite(YELLOW2, LOW);
}

void strum_green()
{
  digitalWrite(GREEN1, HIGH);
  delay(50);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, HIGH);
  delay(50);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, HIGH);
  delay(50);
  digitalWrite(GREEN3, LOW); 
}

void piano_6(double t)
{
  digitalWrite(RED1, HIGH);
  delay(t);
  digitalWrite(RED1, LOW);
  digitalWrite(RED2, HIGH);
  delay(t);
  digitalWrite(RED2, LOW);
  digitalWrite(RED3, HIGH);
  delay(t);
  digitalWrite(RED3, LOW);
  delay(t);
    
  digitalWrite(GREEN1, HIGH);
  delay(t);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, HIGH);
  delay(t);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, HIGH);
  delay(t);
  digitalWrite(GREEN3, LOW);
}

void pluck_1(double t)
{
  digitalWrite(RED1, HIGH);
  delay(t);
  digitalWrite(RED1, LOW);
  digitalWrite(RED2, HIGH);
  delay(t);
  digitalWrite(RED2, LOW);
  digitalWrite(RED3, HIGH);
  delay(t);
  digitalWrite(RED3, LOW);
  digitalWrite(YELLOW1, HIGH);
  delay(t);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(YELLOW2, HIGH);
  delay(t);
  digitalWrite(YELLOW2, LOW);    
  digitalWrite(GREEN1, HIGH);
  delay(t);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, HIGH);
  delay(t);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, HIGH);
  delay(t);
  digitalWrite(GREEN3, LOW);
}

void pluck_2(double t)
{
  
  digitalWrite(RED1, HIGH);
  digitalWrite(RED2, HIGH);
  delay(t);
  digitalWrite(RED1, LOW);
  digitalWrite(RED2, LOW);
  digitalWrite(RED3, HIGH);
  digitalWrite(YELLOW1, HIGH);
  delay(t);
  digitalWrite(RED3, LOW);
  digitalWrite(YELLOW1, LOW);
  digitalWrite(YELLOW2, HIGH);  
  digitalWrite(GREEN1, HIGH);
  delay(t);
  digitalWrite(YELLOW2, LOW);  
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN2, HIGH);
  digitalWrite(GREEN3, HIGH);
  delay(t);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW);
}

void song2()
{
  //youtube.com/watch?v=B4HD6aC4Wos&list=OLAK5uy_lOv-RvzMX9gq5u8lkzrqQSQlorgzq5Blc
   //Make It With You - Ben&Ben
   //play until 1:55
   for(int x = 0; x < 5 ; x++)
   {
    strum_red();
    delay(2900);
    strum_green();
    delay(2900);     
   }
   delay(1900);
  piano_6(500);
  delay(700);
  for(int x = 0; x < 2; x++)
    pluck_1(1600);
  pluck_1(800);  

  for(int x = 0; x < 7; x++)
    pluck_2(1600);
}

void red(double t)
{
  digitalWrite(RED1, HIGH);
  digitalWrite(RED2, HIGH);
  digitalWrite(RED3, HIGH);
  delay(t);  
  digitalWrite(RED2, LOW);
  digitalWrite(RED1, LOW);
  digitalWrite(RED3, LOW);   
}

void yellow(double t)
{
  digitalWrite(YELLOW1, HIGH);
  digitalWrite(YELLOW2, HIGH);
  delay(t);  
  digitalWrite(YELLOW2, LOW);
  digitalWrite(YELLOW1, LOW); 
}

void green(double t)
{
  digitalWrite(GREEN1, HIGH);
  digitalWrite(GREEN2, HIGH);
  digitalWrite(GREEN3, HIGH);
  delay(t);  
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN3, LOW);   
}

void song3()
{
  //https://www.youtube.com/watch?v=-2U0Ivkn2Ds
   //A Great Big World, Christina Aguilera - Say Something
   for(int x = 0; x<300; x++)
   {
    red(1300);
    yellow(1300);
    green(1300);     
   }
}

void by_3_r_l(double t)
{
  digitalWrite(RED1, HIGH);
  delay(t/2);  
  digitalWrite(RED2, HIGH);
  delay(t/2);  
  digitalWrite(RED3, HIGH);
  delay(t);  
  digitalWrite(RED2, LOW);
  digitalWrite(RED1, LOW);
  digitalWrite(RED3, LOW);  
    
  digitalWrite(YELLOW1, HIGH);
  delay(t/2);  
  digitalWrite(YELLOW2, HIGH);
  delay(t);  
  digitalWrite(YELLOW1, LOW);
  digitalWrite(YELLOW2, LOW);
  
  digitalWrite(GREEN3, HIGH);
  delay(t/2);  
  digitalWrite(GREEN2, HIGH);
  delay(t/2);  
  digitalWrite(GREEN1, HIGH);
  delay(t);  
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN3, LOW); 
  digitalWrite(GREEN1, LOW);
}

void green_red(double t)
{
  delay(t);   
  digitalWrite(RED2, LOW);
  digitalWrite(RED1, LOW);
  digitalWrite(RED3, LOW);
  digitalWrite(GREEN2, LOW);
  digitalWrite(GREEN1, LOW);
  digitalWrite(GREEN3, LOW);  
  delay(t);   
  digitalWrite(RED1, HIGH);
  digitalWrite(RED2, HIGH);
  digitalWrite(RED3, HIGH);  
  digitalWrite(GREEN1, HIGH);
  digitalWrite(GREEN2, HIGH);
  digitalWrite(GREEN3, HIGH);
  delay(t);
  off_all();
}

void yellow_last(double t)
{
  green_red(t);
  delay(t);
  yellow(t);
}

void song4()
{
 //https://www.youtube.com/watch?v=E1jrfzDg_ZI
 //My Chemical Romance - I'm Not Okay
  for(int x = 0; x < 5; x++)
    pluck_1(95);
  
  for(int x = 0; x < 2; x++)
    blink_led(280);
  delay(500);
  off_all();
  for(int x = 0; x < 36; x++)
    by_3_r_l(100);
  //@0:28
  prelude();
  pluck_1(50);
  mcr_chorus();
  prelude();
  pluck_1(50);
  mcr_chorus();  
}

void prelude()
{
  for(int x = 0; x < 35; x++)
    yellow_last(125);  
}

void mcr_chorus()
{
  for(int x = 0; x < 100; x++)
    blink_led(100);
  off_all();  
}
