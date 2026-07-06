
#define botonAlarma 2
#define ledAlarma 13

enum Alarma {
  APAGADA,
  CONTANDO_TIEMPO,
  ACTIVADA
};
Alarma estadoAlarma = APAGADA;
unsigned long tiempo = 0;
unsigned long tiempoAhora = 0;

void setup() {
  pinMode(botonAlarma, INPUT_PULLUP);
  pinMode(ledAlarma, OUTPUT);
  digitalWrite(ledAlarma, LOW);  //siempre empieza apagado
  Serial.begin(9600);
}

void loop() {
  int boton = digitalRead(botonAlarma);
  tiempoAhora = millis();

  switch (estadoAlarma) {

    case APAGADA:
      if (boton == LOW) {
        tiempo = tiempoAhora;  //empieza a contar desde ahora 
        estadoAlarma = CONTANDO_TIEMPO;
      }
      break;

    case CONTANDO_TIEMPO:
      if (boton == HIGH) {  // Si sueltan el boton, se cancela la espera
        estadoAlarma = APAGADA;
      } else if (tiempoAhora - tiempo >= 2000) {  // si pasaron 2 segundos con el boton apretado, se prende la alarma
        estadoAlarma = ACTIVADA;
        Serial.println("Alarma activada");
      }
      break;

    case ACTIVADA:
      digitalWrite(ledAlarma, HIGH);
      if (boton == HIGH) {  //si sueltan el boton se apaga la alarma
        digitalWrite(ledAlarma, LOW);
        estadoAlarma = APAGADA;
        Serial.println("Alarma apagada");
      }
      break;
  }
}
