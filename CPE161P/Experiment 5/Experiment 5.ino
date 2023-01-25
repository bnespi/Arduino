#include<TM1637.h>

#define clk 2
#define dio_h_m 3
#define dio_s 4

TM1637 h_m(clk, dio_h_m);
TM1637 s(clk, dio_s);

//for display

//integer displays for each digit
int h_0=0, 
    h_1=8, 
    m_0=5, 
    m_1=2, 
    s_0=0, 
    s_1=0;
long h_past=0, m_past=0, s_past=0;

const long hour = 3600000, minute = 60000, second = 1000;

void setup() {
  // put your setup code here, to run once:
  h_m.init();
  h_m.set(2);

  s.init();
  s.set(2);
}

void loop() {
  // put your main code here, to run repeatedly:

  long long current = millis();

  if(current-s_past >= second)
  {
    s_1++;
    s_past=current;
  }
  if(s_1>9)
  {
    s_0++;
    s_1=0;
  }
  if(s_0>5 && s_1 ==0)
  {
    s_0=0;
    s_1=0;
    m_1++;
  }

  if(current-m_past >= minute)
  {
//    m_1++;
    m_past = current;
  }
  if(m_1>9)
  {
    Serial.println("Increasing tens minute");
    m_0++;
    m_1=0;
  }
  if(m_0>5 && m_1 == 0)
  {
    m_0 = 0;
    m_1 = 0;
    h_1++;
  }

  if(current-h_past >= hour)
  {
//    h_1++;
    h_past = current;
  }
  if(h_1>9)
  {
    h_0++;
    h_1=0;
  }
  if(h_0==1 && h_1 > 2)
  {
    h_0 = 0;
    h_1 = 1;
  }
  
  if(h_0!=0)
    h_m.display(0,h_0);
  h_m.display(1,h_1);
  h_m.point(1);
  h_m.display(2,m_0);
  h_m.display(3,m_1);

  s.display(0,s_0);
  s.display(1,s_1);
}
