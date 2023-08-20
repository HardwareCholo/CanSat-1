#include <SPI.h>
#include <LoRa.h>

#define ss 17
#define rst 16
#define dio0 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Lora Receptor");

  LoRa.setPins(ss, rst, dio0);

  while(!LoRa.begin(915E6)){
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializin ok!");
}

void loop() {
  // put your main code here, to run repeatedly:
  int packetSize = LoRa.parsePacket();
  if(packetSize){
    Serial.print("Received packet: ");
    while(LoRa.available()){
      String LoRaData = LoRa.readString();
      Serial.println(LoRaData);
    }
  }
}