#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SSpin 15

File archivo;

void setup() {
  Serial.begin(9600);
  //Inicialización de la tarjeta SD
  Serial.println("Inicializando tarjeta...");
  if(!SD.begin(SSpin)){
    Serial.println("No SD");
    return;
  }

  //Creación del archivo
  Serial.println("Inicializada");
  archivo = SD.open("/prueba.txt", FILE_WRITE);

  if(archivo){
    archivo.println("Probando 1,2,3");
    Serial.println("Escribiendo en archivo prueba.txt...");
    archivo.close();
    Serial.println("Escritura correcta");
  }
  else{
    Serial.println("Error de apertura de prueba.txt");
  }

  //Lectura del archivo
  archivo = SD.open("/prueba.txt");

  if(archivo){
    Serial.println("Contenido de prueba.txt:");
    while(archivo.available()){
      Serial.write(archivo.read());
    }
    archivo.close();
  }
  else{
    Serial.println("Error de apertura de prueba.txt");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}