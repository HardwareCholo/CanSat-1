#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

const int mpuAddress = 0x68;  //Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);

int16_t ax, ay, az;
int16_t gx, gy, gz;
char lectura;

void setup()
{
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  Wire.begin();
  mpu.initialize();
  Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));
}

void loop()
{
  // Leer las aceleraciones y velocidades angulares
  digitalWrite(12, HIGH);
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);
  delay(500);

  digitalWrite(12, LOW);
  Serial.printf("[%i, %i, %i], [%i, %i, %i]\n",ax,ay,az,gx,gy,gz);
  delay(500);
}