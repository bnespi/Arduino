//#include<String>
#include<Keypad.h>
#include<TM1637.h>

const int rows = 4, cols = 4;

char keys[rows][cols] = 
{
  {'T','0','E','x'},
  {'7','8','9','x'},
  {'4','5','6','x'},
  {'1','2','3','x'}  
};

byte rowpins[rows] = {6,7,8,9}, colpins[cols] = {10,11,12,13}; 

Keypad k_obj = Keypad(makeKeymap(keys), rowpins, colpins, rows, cols);


#define clk A0
#define dio A1

TM1637 tm(clk, dio);

//int servo = 3;

//Servo s;
#define l1 5
#define l2 4
#define l3 3
#define l4 2
#define l5 A2
#define l6 A3

int x = 0;
char in1=' ', in2=' ', in3=' ', in4=' ', in5=' ', in6=' ';
long before, after;

void setup() {
  // put your setup code here, to run once:
  tm.init();
  tm.set(2);

  pinMode(l1, INPUT);
  pinMode(l2, INPUT);
  pinMode(l3, INPUT);
  pinMode(l4, INPUT);
  pinMode(l5, INPUT);
  pinMode(l6, INPUT);
  
  Serial.begin(9600);
  
}

void light_led(int x=0)
{
  switch(x)
  {
    case 0:
      break;
    case 1:
      digitalWrite(l1, HIGH);
      break;
    case 2:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, HIGH);
      break;
    case 3:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, HIGH);
      digitalWrite(l3, HIGH);
      break;
    case 4:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, HIGH);
      digitalWrite(l3, HIGH);
      digitalWrite(l4, HIGH);
      break;
    case 5:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, HIGH);
      digitalWrite(l3, HIGH);
      digitalWrite(l4, HIGH);
      digitalWrite(l5, HIGH);
      break;
    case 6:
      digitalWrite(l1, HIGH);
      digitalWrite(l2, HIGH);
      digitalWrite(l3, HIGH);
      digitalWrite(l4, HIGH);
      digitalWrite(l5, HIGH);
      digitalWrite(l6, HIGH);
      break;
    case 7:
      digitalWrite(l1, LOW);
      digitalWrite(l2, LOW);
      digitalWrite(l3, LOW);
      digitalWrite(l4, LOW);
      digitalWrite(l5, LOW);
      digitalWrite(l6, LOW);
      break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = k_obj.getKey(), first = key;
  int tens=1, ones=0;

  if(
    key == '1' ||
    key == '2' || 
    key == '3' || 
    key == '4' || 
    key == '5' || 
    key == '6' || 
    key == '7' || 
    key == '8' || 
    key == '9' || 
    key == '0'&&
    x!=6
    )
  {
    switch(x)
    {
      case 0:
        in1=key;
        break;
      case 1:
        in2=key;
        break;
      case 2:
        in3=key;
        break;
      case 3:
        in4=key;
        break;
      case 4:
        in5=key;
        break;
      case 5:
        in6=key;
        break;
    }
//    Serial.println(key);
//  Serial.println(in1);
//  Serial.println(in2);
//  Serial.println(in3);
//  Serial.println(in4);
//  Serial.println(in5);
//  Serial.println(in6);
//    Serial.println(x);
    x++;
  }

  if(key=='E'&&x==6)
  {
    Serial.println(key);
    Serial.println(in1=='1'&&in2=='2'&&in3=='3'&&in4=='4'&&in5=='5'&&in6=='6');
    if(
      in1=='1'&&
      in2=='2'&&
      in3=='3'&&
      in4=='4'&&
      in5=='5'&&
      in6=='6'
      )
      {
        digitalWrite(l1, LOW);
        digitalWrite(l2, LOW);
        digitalWrite(l3, LOW);
        digitalWrite(l4, LOW);
        digitalWrite(l5, LOW);
        digitalWrite(l6, LOW);
        after=0;
        while(true)
        {
          before=millis();
          tm.display(0,tens);
          tm.display(1,ones);
//          Serial.println(before-after);
          if(before-after >= 1000)
          {
            after = before;
//            before = millis();
            ones--;
          }

          if(ones<0)
          {
            ones=9;
            tens=0;
          }
          
          if(k_obj.getKey()=='T')
            ones+=5;
          if(ones>9)
          {
            ones-=10;
            tens++;
          }
        }
      }
  }
  
  light_led(x);
  if(x>6)
  {
    in1=' ', in2=' ', in3=' ', in4=' ', in5=' ', in6=' ';
    x=0;
  }
//  delay(1000);
}
