/*
 * IoT-Based Automated Street Lighting System
 * 
 * Automatically switches the street light ON and OFF based on the amount of
 * sunlight present. This is one of the key components of smart cities where
 * energy will be used very efficiently by turning the streetlights ON and OFF
 * at the right time needed. Use Thingspeak for the collection of data
 * and analysis.
 */
#include "WiFiEsp.h"
#include "ThingSpeak.h"
//#include "secret.h"
//#include "SoftwareSerial.h"

unsigned long channelID = 1662870; // under API keys in thingspeak.com
unsigned char * channelAPIkey = "20JWL080G5OAZ2JF"; // under channel settings in thingspeak.com

char ssid[] = "PLDTHOMEFIBRa0b50"; // Wi-Fi name na pagcconnectan
char password[] = "PLDTWIFI5bp2u"; // Wi-Fi password
int keyIndex = 0;
WiFiEspClient client;

#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#define ESP_BAUDRATE  19200
#else
#define ESP_BAUDRATE  115200
#endif

int sensor = A0;
int STlight1 = A1;
int STlight2 = A2;
int STlight3 = A3;
int light_status;
long long before=0, current, d_time = 1000;

void setup() {
  pinMode(sensor, INPUT);
  pinMode(STlight1, OUTPUT);
  pinMode(STlight2, OUTPUT);
  pinMode(STlight3, OUTPUT);

  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  setEspBaudRate(ESP_BAUDRATE);

  while (!Serial) {
    ;
  }

  Serial.print("Searching for ESP8266...");
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Wifi shield not present");
    while (true);
  }
  Serial.println("found it!");

  ThingSpeak.begin(client);

}

void loop() {
  int sunlight = analogRead(sensor);
  current = millis();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

  if(current-before>=d_time)
  {
    if(sunlight>=300)
    {
      digitalWrite(STlight1, LOW);
      digitalWrite(STlight2, LOW);
      digitalWrite(STlight3, LOW);
      light_status = LOW;
    }
    else if(sunlight<120){
      digitalWrite(STlight1, HIGH);
      digitalWrite(STlight2, HIGH);
      digitalWrite(STlight3, HIGH);    
      light_status = HIGH;
    }
  
    ThingSpeak.setField(1, sunlight);
    ThingSpeak.setField(2, light_status);
    ThingSpeak.setField(3, light_status);
    ThingSpeak.setField(4, light_status);
  
    ThingSpeak.writeFields(channelID, channelAPIkey);
  
  Serial.println(sunlight);
  Serial.println(light_status);
  Serial.println(light_status);
  Serial.println(light_status);
  }
 
}

// This function attempts to set the ESP8266 baudrate. Boards with additional hardware serial ports
// can use 115200, otherwise software serial is limited to 19200.
void setEspBaudRate(unsigned long baudrate){
  long rates[6] = {115200,74880,57600,38400,19200,9600};

  Serial.print("Setting ESP8266 baudrate to ");
  Serial.print(baudrate);
  Serial.println("...");

  for(int i = 0; i < 6; i++){
    Serial1.begin(rates[i]);
    delay(100);
    Serial1.print("AT+UART_DEF=");
    Serial1.print(baudrate);
    Serial1.print(",8,1,0,0\r\n");
    delay(100);  
  }
    
  Serial1.begin(baudrate);
}
