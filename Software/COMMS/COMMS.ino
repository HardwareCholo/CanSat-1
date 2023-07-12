#include <SPI.h>
#include <LoRa.h>

#define ss 10
#define rst 5
#define dio0 2

void setup() {
  Serial.begin(9600); // Configurar la velocidad de comunicación UART a 9600 baudios
  Serial.println("Lora Transmisor");
  pinMode(13, OUTPUT);

  LoRa.setPins(ss, rst, dio0);

  while(!LoRa.begin(915E6)){
    Serial.println(".");
    delay(500);
  }

  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializin ok!");
}
String aux,lectura;
void loop() {
  if (Serial.available()) {
    char data = Serial.read(); // Leer los datos recibidos por UART
    aux = String(data);
    lectura = String(lectura + aux);
    if(data == '\0'){
      LoRa.beginPacket();
      LoRa.print(lectura);
      LoRa.endPacket();
      //Serial.println(lectura);
      lectura=' ';   
      }
  }
}
