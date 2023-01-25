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
#include "DHT.h"
//#include "secret.h"
//#include "SoftwareSerial.h"

unsigned long channelID = 1719957; // under API keys in thingspeak.com
unsigned char * channelAPIkey = "K7COHGWQ342CD6HY"; // under channel settings in thingspeak.com

char ssid[] = "PLDTHOMEFIBRa0b50"; // Wi-Fi name na pagcconnectan
char password[] = "PLDTWIFI5bp2u"; // Wi-Fi password
int keyIndex = 0, ts_previous=0, cost_previous=0, open_counter=0, oc_previous=0;
//measuring of time
//millis() and not delay()
WiFiEspClient client;

#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(2, 3); // RX, TX
#define ESP_BAUDRATE  19200
#else
#define ESP_BAUDRATE  115200
#endif

//int DHT11 = A0;
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define ldr A1

int factor = 1;
double energy_cost = 10.22, operation_cost = 0, energy_consumption=0.79;

void setup() {
  pinMode(DHTPIN, INPUT);
  pinMode(ldr, INPUT);

  Serial.begin(115200);
  while (!Serial) {
    ;
  }

  setEspBaudRate(ESP_BAUDRATE);

//  while (!Serial) {
//    ;
//  }

  Serial.print("Searching for ESP8266...");
  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Wifi shield not present");
    while (true);
  }
  Serial.println("found it!");

  ThingSpeak.begin(client);
  
  Serial.println(F("DHTxx test!"));

  dht.begin();
}

void loop() {
  int temp = dht.readTemperature(), ldr_reading = analogRead(ldr);

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


  if(temp<20 && ldr_reading<100)//if door is open
    factor=1.07;
  else
    factor=1;

  //energy_cost = Php10.22/kWh
  //energy_consumption=0.79kWh/24h
  //cost = energy_consumption(kWh/24h) * energy_cost(Pesos/kWh)
  //cost increases by 7% when door is open (based on research)
  //compute cost per second
  //cost = energy_consumption(kWh/24h) * 24h/86400s *energy_cost(Pesos/kWh)
  //cost = energy_consumption(kWh/24h)/86400s *energy_cost(Pesos/kWh)
  if(millis()-cost_previous>=1000)//if a second has passed
  {
    cost_previous=millis();
    operation_cost+=(factor*energy_consumption*energy_cost)/86400;
    Serial.print("P");
    Serial.println(operation_cost, 10);
  }
  
  
  
  if(millis()-ts_previous>=15000)//if a minute has passed
  {
    int x = ThingSpeak.writeFields(channelID, channelAPIkey);
    ThingSpeak.setField(1, ldr_reading);
    ThingSpeak.setField(2, temp);
    ThingSpeak.setField(3, int(operation_cost*10000));
    
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    ts_previous = millis(); 
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
