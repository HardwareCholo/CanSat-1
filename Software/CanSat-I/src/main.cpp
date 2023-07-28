#include <Arduino.h>
#include "Wire.h"
#include <DHT.h>
#include <DHT_U.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "BMP085.h"

//Direcciones I2C
const int mpuAddress = 0x68;  //Puede ser 0x68 o 0x69

//Se crea el objeto de los sensores
DHT dht(23, DHT11);
MPU6050 mpu(mpuAddress);
BMP085 bmp;

//Variables
float t,h = 0.0;
int16_t ax, ay, az;
int16_t gx, gy, gz;
char lectura;
float pressure;
int32_t altitude;


void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  Wire.begin();
  mpu.initialize();
  Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));
  bmp.initialize();
  Serial.println("Testing device connections...");
  Serial.println(bmp.testConnection() ? "BMP085 connection successful" : "BMP085 connection failed");
  bmp.setControl(BMP085_MODE_PRESSURE_3);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Se leen los sensores
  digitalWrite(12, HIGH);
  pressure = bmp.getPressure();
  altitude = bmp.getAltitude(pressure);
  t=dht.readTemperature();
  h=dht.readHumidity();
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);
  delay(1000);

  //Se imprime la lectura
  Serial.printf("%.2f°C\t%.2f%\t[%i, %i, %i]\t[%i, %i, %i]\t%.2fPa\t%im\n",t,h,ax,ay,az,gx,gy,gz,pressure,altitude);
  digitalWrite(12, LOW);
  delay(1000);
}