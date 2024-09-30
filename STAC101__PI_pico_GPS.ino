#include <TinyGPSPlus.h>

TinyGPSPlus gps;


void setup()
{
  
  Serial.begin(115200);
  Serial2.setRX(5);
  Serial2.setTX(4);
  Serial2.begin(9600);
  
  delay(5000);
  Serial.println("Waiting for GPS signal...");
}

void loop() {
  
  while (Serial2.available() > 0) 
  {
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()) {
      Serial.print("Latitude: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitude: ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("UTC Time: ");
      Serial.print(gps.time.hour());
      Serial.print(":");
      Serial.print(gps.time.minute());
      Serial.print(":");
      Serial.println(gps.time.second());
      Serial.println();
    }
  }
}
