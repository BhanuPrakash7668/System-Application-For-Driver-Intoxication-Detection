#include <ESP8266WiFi.h>  //Wifi module library
#include <WiFiClient.h>  //Client wifi connection library

#include <ThingSpeak.h>  //ThingSpeak Cloud library

const char* ssid = "asdfghjk";  //Hotspot Username
const char* password = "12345678";  //Hotspot Password

WiFiClient client;  //client configuration

unsigned long myChannelNumber = 878064;  //Thingspeak channel number
const char * myWriteAPIKey = "I6SK26L40M7BDN0H";  //Thingspeak Write API key

int gas = A0;
#define smoke_dout D0

void setup() {
  Serial.begin(115200);
 
  pinMode(smoke_dout, INPUT);

  pinMode(gas, INPUT);//Use INPUT_PULLUP if output is Open collectors output

  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
  delay(500);  
  Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
  ThingSpeak.begin(client);  
}
 
void loop() {
 
  /*****MQ3 Alcohol Sensor*****/
  int sensorvalue = 0;
  sensorvalue = analogRead(gas);
  Serial.print("Alcohol Sensor Reading: ");
  Serial.println(sensorvalue);
  int dout = digitalRead(smoke_dout);
  Serial.print("Alcohol Digital Value: ");
  Serial.println(dout);
 
  if(digitalRead(smoke_dout) == HIGH)
  {
    Serial.println("Alcohol Detection Alert");
    message1();
    Serial.println("   ");  
    delay(100);
  }
 
  delay(500);

  ThingSpeak.setField(1, sensorvalue);
 
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  
 
  Serial.println("**********************************************");
  Serial.println("   ");
  delay(3000);
}

void message1(void)
{
  Serial.print("AT\r\n");delay(800);
  Serial.print("AT+CMGF=1\r\n");delay(800);
  Serial.print("AT+CMGS=");delay(500);
  Serial.write('"');delay(500);
  Serial.print("7550171050");delay(500);
  Serial.write('"');
  Serial.print("\r\n");delay(500);
  Serial.print("'Alcohol Detection Alert'\r\n");delay(500);//17
  delay(500);
  Serial.write(26);
}
