#include <LoRa.h>
#include <SPI.h>
 
//pico pin
#define ss 17
#define rst 27
#define dio0 28

int counter = 0;
 
void setup() 
{
  Serial.begin(115200); 
  pinMode(LED_BUILTIN,OUTPUT);
  // while (!Serial);
  Serial.println("LoRa Sender");
 
  LoRa.setPins(ss, rst, dio0);    //setup LoRa transceiver module
  
  while (!LoRa.begin(525E6))     //433E6 - Asia, 866E6 - Europe, 915E6 - North America
  {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");
}
 
void loop() 
{
  Serial.print("Sending packet: ");
  Serial.println(counter);
  Serial.println(counter%2);
  LoRa.beginPacket();   //Send LoRa packet to receiver
  LoRa.print("Hello mama hed e yang u nor e mae ");
  LoRa.print(counter);
  LoRa.endPacket();
 
  counter++;
  digitalWrite(LED_BUILTIN, counter%2);

  delay(2000);
}