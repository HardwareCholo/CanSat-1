/*Este software se encarga de controlar la lectura de sensores, el almacenamiento de información de vuelo
y el envío de datos a través de RF*/ 
#include <Arduino.h>
#include <Adafruit_Sensor.h>      //Librería para utilizar el sensor DHT11
#include <DHT.h>
#include <Wire.h>
#include <I2Cdev.h>
#include <BMP085.h>
#include <MPU6050.h>
#include <SPI.h>
#include <LoRa.h>

//Terminales para el LoRa
#define ss 17
#define rst 16
#define dio0 4

//Se crea el objeto de los sensores
DHT dht(33, DHT11);
BMP085 bmp;
MPU6050 mpu(104);

//Variables globales
float h, t, p=0.0;
int32_t a;
int16_t ax, ay, az, gx, gy, gz;
char gps = ' ';

void setup(){
  pinMode(32, OUTPUT);                //Indicador de funcionamiento

  //Inicialización del LoRa
  LoRa.setPins(ss, rst, dio0);
  while(!LoRa.begin(915E6)){
  }
  LoRa.setSyncWord(0xF3); 
  LoRa.beginPacket();
  LoRa.println("COMMS ENABLED");
  LoRa.endPacket(); 
  LoRa.beginPacket();
  LoRa.println("HUITZIL ONLINE");
  LoRa.endPacket();

  //Inicialización de los sensores 
  Wire.begin();
  dht.begin();
  bmp.initialize(); 
  mpu.initialize();
  Serial.println(mpu.testConnection() ? F("IMU iniciado correctamente") : F("Error al iniciar IMU"));
  LoRa.beginPacket();
  LoRa.println("DHT ONLINE");
  LoRa.endPacket();
  LoRa.beginPacket();
  LoRa.println(bmp.testConnection() ? "BMP180 ONLINE" : "BMP180 OFFLINE");
  LoRa.endPacket();
  LoRa.beginPacket();
  LoRa.println(mpu.testConnection() ? "MPU6050 ONLINE" : "MPU6050 OFFLINE");
  LoRa.endPacket();

  digitalWrite(32, HIGH);
  delay(1000);
  digitalWrite(32, LOW);
}

void loop(){
  //Lectura de sensores
  digitalWrite(32, HIGH);
  bmp.setControl(BMP085_MODE_PRESSURE_3);
  p = bmp.getPressure();
  a = bmp.getAltitude(p);
  t=dht.readTemperature();
  h=dht.readHumidity();
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);
  delay(500);

  //Envío de información
  digitalWrite(32, LOW); 
  LoRa.beginPacket();
  LoRa.printf("T%.2fH%.2fP%.2fA%iC%iX%iY%iZ%iG\n",h,t,p,a,az,gx,gy,gz);
  LoRa.endPacket();
  delay(500);
}

