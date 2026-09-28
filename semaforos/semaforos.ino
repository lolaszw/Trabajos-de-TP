//PINES COLUMNA 1
#define PIN_AUTO1_R 4
#define PIN_AUTO1_A 5
#define PIN_AUTO1_V 6
#define PIN_PEATON1_R 7
#define PIN_PEATON1_V 8

//PINES COLUMNA 2
#define PIN_AUTO2_R 9
#define PIN_AUTO2_A 10
#define PIN_AUTO2_V 11
#define PIN_PEATON2_R 12
#define PIN_PEATON2_V 13

//PINES BOTONES
#define PIN_BOTON1 14
#define PIN_BOTON2 15

//DURACIONES (ms) 
const int DURACION_ROJO_AMARILLO = 5000;
const int DURACION_VERDE = 40000;
const int DURACION_AMARILLO =5000;
const int DURACION_ESPERA_BOTON = 5000;

//MAQUINA DE ESTADOS SEMAFORO 1
enum semaforo_1 {
  ROJO,
  ROJO_AMARILLO,
  VERDE,
  AMARILLO
};
semaforo_1 estadoSem_1 = ROJO;

//MAQUINA DE ESTADOS SEMAFORO 2
enum semaforo_2 {
  ROJO_2,
  ROJO_AMARILLO_2,
  VERDE_2,
  AMARILLO_2
};
semaforo_2 estadoSem_2 = VERDE_2;  //arranca en verde para respetar la secuencia pedida

//MAQUINA DE ESTADOS DEL CRUCE (de quien es el turno)
enum cruce {
  SEMAFORO1,
  SEMAFORO2
};
cruce semaforoActual = SEMAFORO2;

unsigned long tiempoAnterior1 = 0;
unsigned long tiempoAnterior2 = 0;

void setup() {
  //semaforo 1
  pinMode(PIN_AUTO1_R, OUTPUT);
  pinMode(PIN_AUTO1_A, OUTPUT);
  pinMode(PIN_AUTO1_V, OUTPUT);
  pinMode(PIN_PEATON1_R, OUTPUT);
  pinMode(PIN_PEATON1_V, OUTPUT);

  //semaforo 2
  pinMode(PIN_AUTO2_R, OUTPUT);
  pinMode(PIN_AUTO2_A, OUTPUT);
  pinMode(PIN_AUTO2_V, OUTPUT);
  pinMode(PIN_PEATON2_R, OUTPUT);
  pinMode(PIN_PEATON2_V, OUTPUT);

  //botones
  pinMode(PIN_BOTON1, INPUT);
  pinMode(PIN_BOTON2, INPUT);


}

//avanza el semaforo 1. Solo se llama cuando es su turno (semaforoActual == SEMAFORO1)
void actSemaforo_1() {
  switch (estadoSem_1) {
    unsigned long ahora = millis();
    case ROJO_AMARILLO:
      {
        digitalWrite(PIN_AUTO1_R, HIGH);
        digitalWrite(PIN_AUTO1_A, HIGH);
        digitalWrite(PIN_AUTO1_V, LOW);
        digitalWrite(PIN_PEATON1_R, LOW);
        digitalWrite(PIN_PEATON1_V, HIGH);

        if (ahora - tiempoAnterior1 >= DURACION_ROJO_AMARILLO) {
          tiempoAnterior1 = ahora;
          estadoSem_1 = VERDE;
        }
        break;
      }
    case VERDE:
      {
        digitalWrite(PIN_AUTO1_R, LOW);
        digitalWrite(PIN_AUTO1_A, LOW);
        digitalWrite(PIN_AUTO1_V, HIGH);
        digitalWrite(PIN_PEATON1_R, HIGH);
        digitalWrite(PIN_PEATON1_V, LOW);

        // Si se presiona el boton y quedan mas de 5 segundos de verde, acorta el tiempo para que queden solo 5 segundos
        if (digitalRead(PIN_BOTON1) == HIGH) {
          if (ahora - tiempoAnterior1 < DURACION_VERDE - DURACION_ESPERA_BOTON) {
            tiempoAnterior1 = ahora - (DURACION_VERDE - DURACION_ESPERA_BOTON);
          }
        }

        if (ahora - tiempoAnterior1 >= DURACION_VERDE) {
          tiempoAnterior1 = ahora;
          estadoSem_1 = AMARILLO;
        }
        break;
      }
    case AMARILLO:
      {
        digitalWrite(PIN_AUTO1_R, LOW);
        digitalWrite(PIN_AUTO1_A, HIGH);
        digitalWrite(PIN_AUTO1_V, LOW);
        digitalWrite(PIN_PEATON1_R, HIGH);
        digitalWrite(PIN_PEATON1_V, LOW);

        if (ahora - tiempoAnterior1 >= DURACION_AMARILLO) {
          tiempoAnterior1 = ahora;
          estadoSem_1 = ROJO;
          //termino su ciclo: le cede el turno al semaforo 2
          semaforoActual = SEMAFORO2;
          estadoSem_2 = ROJO_AMARILLO_2;
          tiempoAnterior2 = ahora;
        }
        break;
      }
    case ROJO:
      {
        //no deberia mantenerse aca mientras es su turno; se deja por las dudas
        digitalWrite(PIN_AUTO1_R, HIGH);
        digitalWrite(PIN_AUTO1_A, LOW);
        digitalWrite(PIN_AUTO1_V, LOW);
        digitalWrite(PIN_PEATON1_R, LOW);
        digitalWrite(PIN_PEATON1_V, HIGH);
        break;
      }
  }
}

//avanza el semaforo 2. Solo se llama cuando es su turno (semaforoActual == SEMAFORO2)
void actSemaforo_2() {
  unsigned long ahora = millis();
  switch (estadoSem_2) {
    case ROJO_AMARILLO_2:
      {
        digitalWrite(PIN_AUTO2_R, HIGH);
        digitalWrite(PIN_AUTO2_A, HIGH);
        digitalWrite(PIN_AUTO2_V, LOW);
        digitalWrite(PIN_PEATON2_R, LOW);
        digitalWrite(PIN_PEATON2_V, HIGH);

        if (ahora - tiempoAnterior2 >= DURACION_ROJO_AMARILLO) {
          tiempoAnterior2 = ahora;
          estadoSem_2 = VERDE_2;
        }
        break;
      }
    case VERDE_2:
      {
        digitalWrite(PIN_AUTO2_R, LOW);
        digitalWrite(PIN_AUTO2_A, LOW);
        digitalWrite(PIN_AUTO2_V, HIGH);
        digitalWrite(PIN_PEATON2_R, HIGH);
        digitalWrite(PIN_PEATON2_V, LOW);

        // Si se presiona el boton y quedan mas de 5 segundos de verde, acorta el tiempo para que queden solo 5 segundos
        if (digitalRead(PIN_BOTON2) == HIGH) {
          if (ahora - tiempoAnterior2 < DURACION_VERDE - DURACION_ESPERA_BOTON) {
            tiempoAnterior2 = ahora - (DURACION_VERDE - DURACION_ESPERA_BOTON);
          }
        }

        if (ahora - tiempoAnterior2 >= DURACION_VERDE) {
          tiempoAnterior2 = ahora;
          estadoSem_2 = AMARILLO_2;
        }
        break;
      }
    case AMARILLO_2:
      {
        digitalWrite(PIN_AUTO2_R, LOW);
        digitalWrite(PIN_AUTO2_A, HIGH);
        digitalWrite(PIN_AUTO2_V, LOW);
        digitalWrite(PIN_PEATON2_R, HIGH);
        digitalWrite(PIN_PEATON2_V, LOW);

        if (ahora - tiempoAnterior2 >= DURACION_AMARILLO) {
          tiempoAnterior2 = ahora;
          estadoSem_2 = ROJO_2;
          //termino su ciclo: le cede el turno al semaforo 1
          semaforoActual = SEMAFORO1;
          estadoSem_1 = ROJO_AMARILLO;
          tiempoAnterior1 = ahora;
        }
        break;
      }
    case ROJO_2:
      {
        //no deberia mantenerse aca mientras es su turno; se deja por las dudas
        digitalWrite(PIN_AUTO2_R, HIGH);
        digitalWrite(PIN_AUTO2_A, LOW);
        digitalWrite(PIN_AUTO2_V, LOW);
        digitalWrite(PIN_PEATON2_R, LOW);
        digitalWrite(PIN_PEATON2_V, HIGH);
        break;
      }
  }
}

void loop() {
  switch (semaforoActual) {
    case SEMAFORO1:
      {
        actSemaforo_1();
        //mientras no es su turno, el semaforo 2 se mantiene fijo en rojo
        digitalWrite(PIN_AUTO2_R, HIGH);
        digitalWrite(PIN_AUTO2_A, LOW);
        digitalWrite(PIN_AUTO2_V, LOW);
        digitalWrite(PIN_PEATON2_R, LOW);
        digitalWrite(PIN_PEATON2_V, HIGH);
        break;
      }
    case SEMAFORO2:
      {
        actSemaforo_2();
        //mientras no es su turno, el semaforo 1 se mantiene fijo en rojo
        digitalWrite(PIN_AUTO1_R, HIGH);
        digitalWrite(PIN_AUTO1_A, LOW);
        digitalWrite(PIN_AUTO1_V, LOW);
        digitalWrite(PIN_PEATON1_R, LOW);
        digitalWrite(PIN_PEATON1_V, HIGH);
        break;
      }
  }
}