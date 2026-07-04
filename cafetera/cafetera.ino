#include <Arduino.h>
#include <AsciiMassage.h>

enum cafetera { ELEGIR,
                SERVIR_LARGO,
                SERVIR_CORTO,
                RETIRAR };
cafetera estadoActual = ELEGIR;

#define botonInicio 3
#define ledSirviendo 4
#define sensorCafe 5

String cafeIngresado = "";

unsigned long tiempo = 0;

void setup() {
  pinMode(botonInicio, INPUT_PULLUP);
  pinMode(ledSirviendo, OUTPUT);
  pinMode(sensorCafe, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  switch (estadoActual) {
    case (ELEGIR):
      {
        if (Serial.available() > 0) {
          cafeIngresado = Serial.readStringUntil('\n');
          cafeIngresado.trim();
        }                                                      //ingresar que tipo de cafe queres
        if (digitalRead(botonInicio) == LOW && cafeIngresado == "corto") {  // cuando presionas el boton empieza a servirse
          estadoActual = SERVIR_CORTO;
          tiempo = millis();
          cafeIngresado = "";
        } else if (digitalRead(botonInicio) == LOW && cafeIngresado == "largo") {
          estadoActual = SERVIR_LARGO;
          tiempo = millis();
          cafeIngresado = "";
        }
        break;
      }
    case (SERVIR_CORTO):
      {

        digitalWrite(ledSirviendo, HIGH);  //muestra que estan sirviendo el cafe
        if (millis() - tiempo >= 3000) {   //si el cafe seleccionado es corto, se sirve por tres segundos
          estadoActual = RETIRAR;
        }


        break;
      }
    case (SERVIR_LARGO):
      {
        digitalWrite(ledSirviendo, HIGH);
        if (millis() - tiempo >= 5000) {  //si el cafe seleccionado es largo, se sirve por cinco segundos
          estadoActual = RETIRAR;
        }
        break;
      }
    case (RETIRAR):
      {
        digitalWrite(ledSirviendo, LOW);       //la cafetera dejo de servir, por ende el led se apaga
        if (digitalRead(sensorCafe) == LOW) {  // el sensor dejo de ver al cafe (lo retiraron), y se reinicia el ciclo
          estadoActual = ELEGIR;
        }
        break;
      }
  }
}
