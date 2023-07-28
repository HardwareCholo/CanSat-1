#include <Arduino.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "BMP085.h"

BMP085 bmp;

float pressure;
int32_t altitude;

void setup() {
    Wire.begin();
    Serial.begin(9600);
    Serial.println("Initializing I2C devices...");
    bmp.initialize();
    Serial.println("Testing device connections...");
    Serial.println(bmp.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");
    pinMode(12, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(12, HIGH);
  bmp.setControl(BMP085_MODE_PRESSURE_3);
  pressure = bmp.getPressure();
  altitude = bmp.getAltitude(pressure);
  delay(500);
  digitalWrite(12, LOW);
  Serial.printf("%.2fPa\t%im\n",pressure,altitude);
  delay(500);
}
