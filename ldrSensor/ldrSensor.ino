#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; 
char server[] = "server";
EthernetClient client;

char appKey[] = "appkey";
char thingName[] = "ThingMaster";
char serviceName[] = "setHeartBeat";
int timeBetweenRefresh = 1000;
unsigned long lastConnectionTime = 0;

int ldr_pin = A0;
bool ldr_value=false;
int ldr_read=0;
  
void setup(){
  Serial.begin(9600);
  Serial.println("Trying to get an IP address using DHCP");
  Ethernet.begin(mac);
  Serial.print("My IP address: ");  Serial.print(Ethernet.localIP());  Serial.println();
  
}
  
void loop(){
  if (millis() - lastConnectionTime > timeBetweenRefresh){
    updateValues();    
  }    
  else{
    updateSensorsValue();
  }  
}

void updateSensorsValue(){
  /*
  if(analogRead(ldr_pin)<34){
    ldr_value=true;
  }
  else{
    ldr_value=true;
  }
  
  Serial.print("Light Present: ")
  Serial.println(ldr_value);
  */
  ldr_read=analogRead(ldr_pin);
  Serial.println(ldr_read);
  delay(500);
}
void updateValues()
{
  if (client.connect(server, 8080)) {
      if(client.connected()){
        // Sending a header of a network packet  
        Serial.println("Sending data to IoT server...\n");  
        Serial.print("POST /Thingworx/Things/");  client.print("POST /Thingworx/Things/"); 
        Serial.print(thingName);  client.print(thingName);  
        Serial.print("/Services/");  client.print("/Services/");  
        Serial.print(serviceName);   client.print(serviceName); 
        Serial.print("?appKey=");    client.print("?appKey=");  
        Serial.print(appKey);        client.print(appKey);  
        Serial.print("&method=post&x-thingworx-session=true");  client.print("&method=post&x-thingworx-session=true"); 
        Serial.print("&");  client.print("&");  
        Serial.print("hb"); client.print("hb");  
        Serial.print("=");  client.print("=");
      
        Serial.print(ldr_read);  client.print(ldr_read);  
        
        Serial.println(" HTTP/1.1");  client.println(" HTTP/1.1");  
        Serial.println("Accept: application/json");  client.println("Accept: application/json");  
        Serial.print("Host: ");  client.print("Host: ");  
        Serial.println(server);  client.println(server);  
        Serial.println("Content-Type: application/json"); client.println("Content-Type: application/json");  
        Serial.println();  client.println();  

        client.stop();  
        lastConnectionTime = millis();
      }
    }
    else{
      Serial.println("Connection could not be established");  
      client.stop();
    }
  }
