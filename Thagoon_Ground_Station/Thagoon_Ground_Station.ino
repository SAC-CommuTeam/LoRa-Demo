#include <SPI.h>
#include <LoRa.h>

//esp32 pin
#define ss 4
#define rst 5
#define dio0 2

long INT_Lat = 0;
long INT_Lon = 0;

float Float_Lat = 0;
float Float_Lon = 0;

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
      // String LoRaData = "lat_Packet :13652008, lng_Packet :100494337";  //Example Test
      String LoRaData = LoRa.readString();
      // Serial.print(LoRaData); 
      sscanf(LoRaData.c_str(),"lat_Packet :%ld, lng_Packet :%ld",&INT_Lat, &INT_Lon);
      Float_Lat = (float)INT_Lat/1000000;
      Float_Lon = (float)INT_Lon/1000000;
      Serial.print("Lat : ");
      Serial.print(Float_Lat,6);
      Serial.print(" ,Lon : ");
      Serial.println(Float_Lon,6);

      // print RSSI of packet
      Serial.print("' with RSSI ");
      Serial.println(LoRa.packetRssi());

    }
  }
}
