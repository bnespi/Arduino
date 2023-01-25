#include<ThingSpeak.h>
#include<WiFi.h>

//declare wifi credentials with api info
char ssid[] = "PLDTHOMEFIBRa0b50";
char pass[] = "PLDTWIFI5bp2u";
unsigned long myChannelNumber = 1691819;
const char *myWriteAPIKey = "V5VQKSAJXFW9WU37";

//create wifi client
WiFiClient c;


//variables
#define ldr 36
#define ldr_2 39

int reading, reading_2, previous=0, max_p = 5 ,people=0;

#define led_1 12
#define led_2 14
#define led_3 27
#define led_4 33
#define led_5 32

void setup() {
  // put your setup code here, to run once:
  
  //set sensor pinmode
  pinMode(ldr, INPUT);
  pinMode(ldr_2, INPUT);

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);


  //make sure the serial port is connected
  Serial.begin(115200);
  while(!Serial){
  }
  //declare wifi mode
  WiFi.mode(WIFI_STA);
  //begin thingspeak with client
  ThingSpeak.begin(c);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  //make sure that the WiFi is connected
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  //to smoothen the readings of the light-dependent sensors, the reading would be done every 100 milliseconds
  if(millis()-previous>=100)
  {
    reading=digitalRead(ldr);
    reading_2=digitalRead(ldr_2);

    previous=millis();
  }
  
//  Serial.print(reading);
//  Serial.print(' ');
//  Serial.print(reading_2);
//  Serial.println(' ');
//  Serial.println(people);

  //people going out of the room
  while(reading)
  {
    reading=digitalRead(ldr);

    delay(100);
    if(!reading)
      people--;
  }

  //people going in the room
  while(!reading_2)
  {
    reading_2=digitalRead(ldr_2);

    delay(100);
    if(reading_2)
      people++;
  }

  //people inside is greater than 5
  if(people>max_p)
    people=max_p;
  //if people variable is negative
  if(people<0)
    people=0;

  switch(people)
  {
    case 1:
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, LOW);
      digitalWrite(led_3, LOW);
      digitalWrite(led_4, LOW);
      digitalWrite(led_5, LOW);
      break;
    case 2:
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, LOW);
      digitalWrite(led_4, LOW);
      digitalWrite(led_5, LOW);
      break;
    case 3:
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, HIGH);
      digitalWrite(led_4, LOW);
      digitalWrite(led_5, LOW);
      break;
    case 4:
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, HIGH);
      digitalWrite(led_4, HIGH);
      digitalWrite(led_5, LOW);
      break;
    case 5:
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, HIGH);
      digitalWrite(led_4, HIGH);
      digitalWrite(led_5, HIGH);
      break;
    //case 0:
    default:
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, LOW);
      digitalWrite(led_3, LOW);
      digitalWrite(led_4, LOW);
      digitalWrite(led_5, LOW);
  }
  
  if(millis()-previous>=60000)//if a minute has passed
  {
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    ThingSpeak.setField(1, people);
    ThingSpeak.setField(2, reading_2); //Inflow Monitor
    ThingSpeak.setField(3, reading); //Outflow Monitor
    
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    previous = millis(); 
  }
}
