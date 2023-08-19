#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SSpin 5

File archivo;			// objeto archivo del tipo File

void setup() {
  Serial.begin(9600);				// inicializa monitor serie a 9600 bps
  Serial.println("Inicializando tarjeta ...");	// texto en ventana de monitor
  if (!SD.begin(SSpin)) {			// inicializacion de tarjeta SD
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;					// se sale del setup() para finalizar el programa
  }
  
  Serial.println("inicializacion correcta");	// texto de inicializacion correcta
  archivo = SD.open("/prueba.txt", FILE_WRITE);	// apertura para lectura/escritura de archivo prueba.txt

  if (archivo) {
    archivo.println("Probando 1, 2, 3");	// escritura de una linea de texto en archivo
    Serial.println("Escribiendo en archivo prueba.txt...");	// texto en monitor serie
    archivo.close();				// cierre del archivo
    Serial.println("escritura correcta");	// texto de escritura correcta en monitor serie
  } else {
    Serial.println("error en apertura de prueba.txt");	// texto de falla en apertura de archivo
  }

  archivo = SD.open("/prueba.txt");		// apertura de archivo prueba.txt
  if (archivo) {
    Serial.println("Contenido de prueba.txt:");	// texto en monitor serie
    while (archivo.available()) {		// mientras exista contenido en el archivo
      Serial.write(archivo.read());  		// lectura de a un caracter por vez
    }
    archivo.close();				// cierre de archivo
  } else {
    Serial.println("error en la apertura de prueba.txt");// texto de falla en apertura de archivo
  }
}

void loop() {			// funcion loop() obligatoria de declarar pero no utilizada
  // nada por aqui
}