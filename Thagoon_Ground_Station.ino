#include <SPI.h>
#include <LoRa.h>

//esp32 pin
#define ss 4
#define rst 5
#define dio0 2

#define INPUT_SIZE 50

char input[INPUT_SIZE+1]

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(525E6)) { //525MHz
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xA5);
  Serial.println("LoRa Initializing OK!");

  
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {

    // read packet
    while (LoRa.available())
    {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
      char* a = strok(LoRaData, ",");
      while(a != 0){
        char* sep = strchr(LoRaData, ":");
        if(sep != 0){
          *sep = 0;
          int LAT = atoi(LoRaData);
          ++sep;
          int LONG = atoi(9
          
        } 
      }
    }

    // print RSSI of packet

    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
