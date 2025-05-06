#define SPEAKER_PIN 8

// Frequências das notas musicais (em Hz)
#define NOTE_C4  262  // Dó (C4)
#define NOTE_D4  294  // Ré (D4)
#define NOTE_E4  330  // Mi (E4)
#define NOTE_F4  349  // Fá (F4)
#define NOTE_G4  392  // Sol (G4)
#define NOTE_A4  440  // Lá (A4)
#define NOTE_B4  494  // Si (B4)
#define NOTE_C5  523  // Dó (C5)

void setup() {
  pinMode(12, INPUT_PULLUP);  // Botão 1
  pinMode(11, INPUT_PULLUP);  // Botão 2
  pinMode(10, INPUT_PULLUP);  // Botão 3
  pinMode(9, INPUT_PULLUP);   // Botão 4
  pinMode(7, INPUT_PULLUP);   // Botão 5
  pinMode(6, INPUT_PULLUP);   // Botão 6
  pinMode(5, INPUT_PULLUP);   // Botão 7
  pinMode(4, INPUT_PULLUP);   // Botão 8
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(12) == LOW) {
    tone(SPEAKER_PIN, NOTE_C4);  // Toca a nota C4
  } else if (digitalRead(11) == LOW) {
    tone(SPEAKER_PIN, NOTE_D4);  // Toca a nota D4
  } else if (digitalRead(10) == LOW) {
    tone(SPEAKER_PIN, NOTE_E4);  // Toca a nota E4
  } else if (digitalRead(9) == LOW) {
    tone(SPEAKER_PIN, NOTE_F4);  // Toca a nota F4
  } else if (digitalRead(7) == LOW) {
    tone(SPEAKER_PIN, NOTE_G4);  // Toca a nota G4
  } else if (digitalRead(6) == LOW) {
    tone(SPEAKER_PIN, NOTE_A4);  // Toca a nota A4
  } else if (digitalRead(5) == LOW) {
    tone(SPEAKER_PIN, NOTE_B4);  // Toca a nota B4
  } else if (digitalRead(4) == LOW) {
    tone(SPEAKER_PIN, NOTE_C5);  // Toca a nota C5
  } else {
    noTone(SPEAKER_PIN);  // Para de tocar se nenhum botão estiver pressionado
  }
}