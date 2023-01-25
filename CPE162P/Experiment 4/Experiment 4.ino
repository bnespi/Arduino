#include<Stepper.h>
#include<WiFi.h>
#include<ThingSpeak.h>

#define IN1 12
#define IN2 14
#define IN3 27
#define IN4 26
#define sensor 36

//rotation is 512 for 90-degree rotation
int rotation = 500, dt = 50, motor_speed = 60;
Stepper motor(rotation, IN1, IN3, IN2, IN4);

WiFiClient c;

char ssid[] = "PLDTHOMEFIBRa0b50";   // your network SSID (name) 
char pass[] = "PLDTWIFI5bp2u";   // your network password
int previous = 0;
unsigned long myChannelNumber = 1678344;
const char * myWriteAPIKey =  "LPZX6F7C3BFHEYO5";

void setup() {
  // put your setup code here, to run once:
  motor.setSpeed(motor_speed);
  pinMode(sensor, INPUT);
  delay(1000);

  Serial.begin(115200);
  while (!Serial) {
    // wait for serial port to connect. Needed for Leonardo native USB port only
  }

  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(c);
}

void loop() {
  // put your main code here, to run repeatedly:
//  motor.step(1000);
//  delay(1000);
//  motor.step(0);
//  delay(1000);
//  motor.step(-1000);
//  delay(1000);

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
  
  int output_value = analogRead(sensor);
  output_value = map(output_value,4095,0,0,100);
  Serial.println(output_value);

  if(output_value<30)
  {
    motor.step(1000);
    delay(1000);
    motor.step(0);
  }

  //write to thingspeak
  if(millis() - previous > 15000)
  {
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    ThingSpeak.setField(1, output_value);
//    ThingSpeak.setField(2, humid);
    
    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    previous = millis(); 
  }
}
