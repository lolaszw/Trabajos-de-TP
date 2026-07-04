
enum microondas {CONTANDO, COCINANDO};

#define botonIncremento 2;
#define botonDecrecimiento 3;
#define botonInicio 4;
#define ledCocinando 5;

microondas estadoActual = CONTANDO;
int tiempoMicro = 0; 

unsigned long tiempo = 0;

int estadoAnteriorIncremento = HIGH;
int estadoAnteriorDecrecimiento = HIGH;
int estadoAnteriorInicio = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(botonIncremento, INPUT_PULLUP);
  pinMode(botonDecrecimiento, INPUT_PULLUP);
  pinMode(botonInicio, INPUT_PULLUP);
  pinMode(ledCocinando, OUTPUT);

  digitalWrite(ledCocinando, LOW);

  Serial.print("Tiempo configurado: ");
  Serial.print(tiempoMicro);
  Serial.println(" s");
}

void loop() {

  switch (estado) {

    case CONTANDO: {
      int estadoIncremento = digitalRead(botonIncremento);
      int estadoDecrecimiento = digitalRead(botonDecrecimiento);
      int estadoInicio = digitalRead(botonInicio);

      if (estadoIncremento == LOW && estadoAnteriorIncremento == HIGH) { //cuando pulsas el boton de incremento, se suma un segundo
        tiempoMicro++;
        Serial.print("Tiempo configurado: ");
        Serial.print(tiempoMicro);
        Serial.println(" s");
      }

      if (estadoDecrecimiento == LOW && estadoAnteriorDecrecimiento == HIGH) { //cuando pulsas el boton de decrecimiento, se resta un segundo
        if (tiempoMicro > 0) {
          tiempoMicro--;
        }
        Serial.print("Tiempo configurado: ");
        Serial.print(tiempoMicro);
        Serial.println(" s");
      }

      if (estadoInicio == LOW && estadoAnteriorInicio == HIGH && tiempoMicro > 0) { //cuando se presiona el boton de inicio, empieza a cocinar
        tiempo = millis();
        digitalWrite(ledCocinando, HIGH);
        estadoActual = COCINANDO;
      }

      estadoAnteriorIncremento = estadoIncremento; //esto sirve para guardar el estado anterior del boton y evitar que hayan errores
      estadoAnteriorDecrecimiento = estadoDecrecimiento;
      estadoAnteriorInicio = estadoInicio;
      break;
    }

    case COCINANDO:
      if (millis() - tiempo >= 1000) { //cada que pasa un segundo, se descuenta un segundo al tiempo de coccion
        tiempo = millis();
        tiempoMicro--;

        Serial.print("Tiempo restante: ");
        Serial.print(tiempoSegundos);
        Serial.println(" s");

        if (tiempoMicro <= 0) {
          tiempoMicro = 0;
          digitalWrite(ledCocinando, LOW);
          estadoActual = CONTANDO;
        }
      }
      break;
  }
}
