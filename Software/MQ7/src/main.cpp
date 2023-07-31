#include <Arduino.h>

int lectura_an, valor_mq7;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12, HIGH);
  lectura_an = analogRead(36);
  valor_mq7 = map(lectura_an,0,1023,0,100);
  delay(500);
  Serial.println(valor_mq7);
  digitalWrite(12, LOW);
  delay(500);
}
