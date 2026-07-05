

#define botonInicio  2;
#define botonPausa 3;


enum Estado { apagado,
              contando,
              pausado };
Estado estado = apagado;

int segundos = 0;
int minutos = 0;

unsigned long tiempo = 0;  


int anteriorInicio = HIGH;
int anteriorPausa = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(botonInicio, INPUT_PULLUP);
  pinMode(botonPausa, INPUT_PULLUP);
  Serial.println("00:00");
}

void loop() {

  int estadoInicio = digitalRead(botonInicio);
  int estadoPausa = digitalRead(botonPausa);

  anteriorInicio = estadoInicio;
  anteriorPausa = estadoPausa;


  switch (estado) {
    case (apagado):
      {
        segundos = 0;
        minutos = 0;
        Serial.println(minutos
                       : segundos);
        if (estadoInicio == LOW && anteriorInicio == HIGH) {  //si se presiona el boton de inicio, empieza a contar
          estado = contando;
          tiempo = millis();
        }
        break;
      }
    case (contando):
      {
        if (millis() - tiempo >= 1000) {  //cada un segundo, se incrementan los segundos
          segundos++;
        }
        if (segundos >= 60) {  //cuando llega a los 60 segundos, se incrementa el minuto y los segundos se reinician
          segundos = 0;
          minutos++;
        }
        Serial.println(minutos
                       : segundos);            //lo muestra por el serial port
        if (estadoPausa == LOW && anteriorPausa == HIGH) {  //si se presiona el boton de pausa
          estado = pausado;
        }
        if (estadoInicio == LOW && anteriorInicio == HIGH) {  //si se presiona el boton de inicio, se apaga el timer
          estado = apagado;
        }
        break;
      }
    case (pausado):
      {
        Serial.println(minutos
                       : segundos);  //muestra como va el tiempo

        if (estadoPausa == LOW && anteriorPausa == HIGH) {  //si se presiona el boton de pausa, sigue contando
          estado = contando;
          tiempo=millis();
        }
        if (estadoInicio == LOW && anteriorInicio == HIGH) {  //si se presiona el boton de inicio, se apaga el timer
          estado = apagado;
        }
        break;
      }
  }
