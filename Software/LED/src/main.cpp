#include <Arduino.h>

void setup() {
  pinMode(32, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(32, HIGH);
  Serial.println("HIGH");
  delay(250);
  digitalWrite(32, LOW);
  Serial.println("LOW");
  delay(250);
}
