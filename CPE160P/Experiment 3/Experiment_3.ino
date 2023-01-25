#define D1 2
#define D2 3
#define D3 4
#define D4 5
#define a 6
#define b 7
#define c 8
#define d 9
#define e 10
#define f 11
#define g 12
#define hours_inc A0
#define minutes_inc A1
#define hour 3600000 //STAND FOR AN HOUR IN MILLISECONDS
#define minute 60000 //STAND FOR A MINUTE IN MILLISECONDS

//for displays
//d1_seq and d2_seq are digit 1 and digit 2 sequence respectively
//they have their own counters d1_ctr and d2_ctr
//the array's sequence is a pairwise sequence of what D1 and D2 should have
//sample:
//1&2, 0&1, 0&2, etc.
int d1_seq[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}, d1_ctr = 0;
int d2_seq[12] = {2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1}, d2_ctr = 0;
//D3 and D4 display will be discrete
//there will be a logic to limit the D3 to 5 and D4 to 9
int d3_disp = 0, d4_disp = 0;

//these are for counting the time 
unsigned long start_hour = 0, start_min = 0;

//write functions
void write_D1(int disp=0);
void write_D2(int disp=0);
void write_D3(int disp=0);
void write_D4(int disp=0);
void write_num(int num = 0);

//turn every led of the current digit off
void off_all();

void setup() {
  // put your setup code here, to run once:
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

  pinMode(hours_inc, INPUT);
  pinMode(minutes_inc, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //time counter
  unsigned long current = millis();

  //read buttons
  int hour_state=digitalRead(hours_inc), min_state = digitalRead(minutes_inc);


  //for pressing button
  //if hour_inc is pressed
  if(hour_state==HIGH)
  {
      //change hour displays        
      d1_ctr++; 
      d2_ctr++; 
      delay(100);
  }

  //if minutes_inc is pressed
  if(min_state==HIGH)
  {
      d4_disp++;
      delay(100);
  }
  
  //if the counter for d1_seq is 12 then d2_ctr is also 12
  //reset to 0
  if(d1_ctr == 12)
  {
    d1_ctr = 0;
    d2_ctr = 0;  
  }

  //initialize to 12:00
  if(start_min == 0)
  {
      write_D1(d1_seq[d1_ctr]); //1
      write_D2(d2_seq[d2_ctr]); //2
      write_D3(d3_disp);        //0
      write_D4(d4_disp);        //0
  } 
  
  //loop for hour increment
  //format:
  /*
    - increment the counters for d1_seq and d2_seq
    - check if ctr is 12 to reset to 0
    - set start_hour to current millis()
  */
  if(current-start_hour>=hour)//IF AN HOUR HAS PASSED
   {
      //change hour displays        
      d1_ctr++; 
      d2_ctr++;
      
      if(d1_ctr == 12)
      {
        d1_ctr = 0;
        d2_ctr = 0;  
      }
      
      start_hour = current;
   } 

   //loop for minute increment
   //format: 
   /*
    - increase the d4_disp (d4_disp is discretely what will be shown on D4)
    - set start_min to current millis()
   */
   if(current-start_min>=minute)//IF A MINUTE HAS PASSED
   {
      d4_disp++;
      start_min = current;  
   }

   //checker if d4_disp is now 10
   //reset d4_disp to 0 then increment d3_disp (d3_disp is also discretely what will be shown on D3)
   if(d4_disp==10)
   {
    d4_disp = 0;
    d3_disp++;   
   }

   //if D3D4 is 60
   // then set D3D4 to 00
   if(d3_disp==6 && d4_disp==0)
   {
    d4_disp = 0;
    d3_disp = 0;
    if(hour_state==HIGH)
    {
      //change hour displays        
      d1_ctr++; 
      d2_ctr++; 
    }
   }

   //write functions for D1, D2, D3, D4
    write_D1(d1_seq[d1_ctr]);
    write_D2(d2_seq[d2_ctr]); 
    write_D3(d3_disp);
    write_D4(d4_disp);   
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
