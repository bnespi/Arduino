#define TOP 2
#define R1 3
#define R2 4
#define BTTM 5
#define L2 6
#define L1 7
#define MID 8
#define s4 A0
#define s3 A1
#define s2 A3
#define s1 A4
#define e1 10
#define e2 11
#define e3 12
#define e4 13

void setup() {
  // put your setup code here, to run once:
  pinMode(TOP, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(BTTM, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(MID, OUTPUT);

  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);
  pinMode(e3, OUTPUT);
  pinMode(e4, OUTPUT);

  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int A=digitalRead(s1), B=digitalRead(s2), C=digitalRead(s3), D=digitalRead(s4);

  BINtoHEX(A,B,C,D);
  BINtoGRAY(A, B, C, D);
  
}

void BINtoHEX(int A, int B, int C, int D)
{
  int a= (A||B||C||!D)&&(A||!B||C||D)&&(!A||!B||C||!D)&&(!A||B||!C||!D),
  b= (A||!B||C||!D)&&(!B||!C||D)&&(!A||!B||D)&&(!A||!D||!C),
  c= (!A||!B||C||D)&&(!A||!B||!C)&&(A||B||!C||D),
  d= (A||!B||C||D)&&(A||B||C||!D)&&(!B||!C||!D)&&(!A||B||!C||D),
  e= (A||!B||C)&&(A||!D)&&(B||C||!D),
  f= (A||B||!C)&&(!A||!B||C||!D)&&(A||B||!D)&&(A||!C||!D),
  g= (A||B||C)&&(!A||!B||C||D)&&(A||!B||!C||!D);

  digitalWrite(TOP, a);
  digitalWrite(R1, b);
  digitalWrite(R2, c);
  digitalWrite(BTTM, d);
  digitalWrite(L2, e);
  digitalWrite(L1, f);
  digitalWrite(MID, g);
}

void BINtoGRAY(int A, int B, int C, int D)
{
  int a= A,
  b= B^A,
  c= B^C,
  d= C^D;

  digitalWrite(e1, d);
  digitalWrite(e2, c);
  digitalWrite(e3, b);
  digitalWrite(e4, a);
}
