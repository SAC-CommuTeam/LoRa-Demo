#include <TinyGPSPlus.h>
#include <LoRa.h>
#include <SPI.h>
 
//pico pin
#define ss 17
#define rst 27
#define dio0 28
TinyGPSPlus gps;

unsigned long previousMillis = 0;   
long lat_Packet = 0;
int counter = 0;
long lng_Packet = 0;


void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  Serial2.setRX(5);
  Serial2.setTX(4);
  Serial2.begin(9600);
  
  delay(5000);
  LoRa.setPins(ss, rst, dio0); 

  
  while (!LoRa.begin(525E6))    
  {
    Serial.println(".");
    delay(500);
  }
  
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
  Serial.println("Waiting for GPS signal...");
}

void loop() 
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= 1000) 
  {
    Serial.println(lat_Packet);
    Serial.println(lng_Packet);
      if (lat_Packet !=0 && lat_Packet !=0 )
      {
        Serial.println("GPS : Connect ");
        LoRa.beginPacket();   
        LoRa.print("lat_Packet :");
        LoRa.print(lat_Packet);
        LoRa.print(", lng_Packet :");
        LoRa.print(lng_Packet);
        LoRa.endPacket();
        counter++;
        digitalWrite(LED_BUILTIN, counter%2);
        previousMillis = currentMillis;
      }
      
       else
      {
        Serial.println("GPS : Disconnect ");
        LoRa.beginPacket();   
        LoRa.print("GPS : Disconnect");
        LoRa.endPacket();
        counter++;
        digitalWrite(LED_BUILTIN, counter%2);
        previousMillis = currentMillis;
      }
      
  }
  
  while(Serial2.available() > 0) 
  {
    gps.encode(Serial2.read());
//    if (gps.location.isUpdated()) 
//    {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);

      lat_Packet = gps.location.lat()*1000000;
      lng_Packet = gps.location.lng()*1000000;
//    }
  }
}
