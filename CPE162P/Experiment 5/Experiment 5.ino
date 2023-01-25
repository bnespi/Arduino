#include<ThingSpeak.h>
#include<WiFi.h>

//declare the GPIO pin for sensor
#define water_sensor 39
//declare wifi credentials with api info
char ssid[] = "Ben 10";
char pass[] = "Ben 10thousand";
unsigned long myChannelNumber = 1684721;
const char *myWriteAPIKey = "FZ5R28OKSYZSV1EP";
int previous = 0;


//create wifi client
WiFiClient c;


void setup() {
  // put your setup code here, to run once:
  
  //set sensor pinmode
  pinMode(water_sensor, INPUT);
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

  //read the water level sensor: 0-4095. 4095 is the minimum and 0 is the maximum.
  //using the map function to set 4095 as 0% and 0 as 100%
  float water_level = analogRead(water_sensor), sensor_reading = water_level;
//  Serial.print(sensor_reading);
//  Serial.print("\t");
  
  water_level = map(water_level, 0, 1500, 0, 100);
  water_level = water_level*2;
//  Serial.println(water_level);

  if(millis()-previous>=60000)//if a second has passed
  {
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    ThingSpeak.setField(1, water_level);
    ThingSpeak.setField(2, sensor_reading);
    
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    previous = millis(); 
  }
}
