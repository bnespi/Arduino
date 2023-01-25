#include <WiFi.h>
#include "ThingSpeak.h" 
#include <dht.h>
char ssid[] = "PLDTHOMEFIBRa0b50";   // your network SSID (name) 
char pass[] = "PLDTWIFI5bp2u";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = 1671725;
const char * myWriteAPIKey =  "AI6NVCT6INVXJ2QZ";

dht DHT;
int dhtPin = 15;
int previous = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // Connect or reconnect to WiFi
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
  int sensorValue = DHT.read11(dhtPin);

  Serial.print("Humidity");
  Serial.println(DHT.humidity);
  delay(1000);
  
  Serial.print("Temperature ");
  Serial.print(DHT.temperature);
  Serial.println(" C");
  delay(1000);

  int humid = DHT.humidity;
  int temp = DHT.temperature;
  
  if(millis() - previous > 15000)
  {
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    ThingSpeak.setField(1, temp);
    ThingSpeak.setField(2, humid);
    
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    previous = millis(); 
  }
}


//Function to connect ESP32 to internet
//Less space used for the main loop
/*void wifiConnect()
{
    if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println("GlobeAtHome_6ea28_2.4");
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
}*/
