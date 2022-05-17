#include <SPI.h>
#include <LoRa.h>

#define ss 5
#define rst 14
#define dio0 2

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
  if(!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    digitalWrite(26, HIGH);
    while (1);
  }else{
    Serial.println("yoot");
  }
}

void loop() {

  if(Serial.available() > 1){
      LoRa.beginPacket();
      LoRa.print("armed");
      LoRa.endPacket();
      Serial.println("Armed");
      
      delay(100);
  }

  // send packet

 int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
  
}