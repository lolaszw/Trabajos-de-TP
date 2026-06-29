// ============================================================
// CRONOMETRO SIMPLE (sin antirrebote) - máquina de estados + millis()
// D2 = START/PAUSE   D3 = STOP/RESET   (a GND, INPUT_PULLUP)
// ============================================================

const int botonInicio = 2;
const int botonPausa = 3;

// --- Estados del cronómetro ---
enum Estado { apagado,
              contando,
              pausado };
Estado estado = apagado;

int segundos = 0;
int minutos = 0;

unsigned long ultimoSegundo = 0;  // último momento en que sumamos 1 segundo

// Para detectar el momento exacto en que se presiona el botón (flanco)
int anteriorStart = HIGH;
int anteriorStop = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(botonInicio, INPUT_PULLUP);
  pinMode(botonPausa, INPUT_PULLUP);
  Serial.println("Cronometro listo. 00:00");
}

void loop() {
  // --- Leer botones (sin antirrebote) ---
  int actualStart = digitalRead(botonInicio);
  int actualStop = digitalRead(botonPausa);

  bool pulsoStart = (actualStart == LOW && anteriorStart == HIGH);
  bool pulsoStop = (actualStop == LOW && anteriorStop == HIGH);

  anteriorStart = actualStart;
  anteriorStop = actualStop;

  // --- Máquina de estados del cronómetro ---
  if (pulsoStart) {
    if (estado == apagado || estado == pausado) {
      estado = contando;
    } else {
      estado = pausado;
    }
  }

  if (pulsoStop) {
    estado = apagado;
    segundos = 0;
    minutos = 0;
    Serial.println(minutos : segundos);
  }

  // --- "Timer" de 1 segundo usando millis() ---
  if (estado == contando && millis() - ultimoSegundo >= 1000) {
    ultimoSegundo = millis();
    segundos++;
    if (segundos >= 60) {
      segundos = 0;
      minutos++;
    }
    Serial.println(minutos : segundos);
  }
}