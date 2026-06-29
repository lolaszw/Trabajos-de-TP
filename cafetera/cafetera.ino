enum cafetera { elegir,
                servir,
                dispensando,
                retirar };
cafetera estadoActual = elegir;

#define botonInicio 3
#define ledSirviendo 4
#define sensorCafe 5

unsigned long tiempo = 0;

void setup() {
  pinMode(botonInicio, INPUT_PULLUP);
  pinMode(ledSirviendo, OUTPUT);
  pinMode(sensorCafe, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  switch (cafetera) {
    case (elegir):
      {
        int cafeElegido = Serial.write();
        if (botonInicio == LOW) {
          estadoActual = servir;
          tiempo = millis();
      }
    case (servir):
      {
        if (cafeElegido == corto) {
          digitalWrite(ledSirviendo, HIGH);
        }
      }
  }
}
