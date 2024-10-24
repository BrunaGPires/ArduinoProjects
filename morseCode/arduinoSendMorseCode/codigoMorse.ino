// Componentes
#define LED 2
#define BUZZER 4

// Armazena palavra
String str = "";
// Verifica se já foi
bool status = false;

void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  Serial.setTimeout(10);
  Serial.println("Starting...");
  delay(1000);
}

void loop() {
  receive();

  if (status == false) {
    translate();

    // Limpa a string depois de traduzir e reseta o status
    str = "";
    status = false;    
  }
  
}

// Le o que usuario digitou no serial
void receive() {
  if (Serial.available() > 0) {
    str = Serial.readStringUntil('\n');
    str.trim();
    Serial.println(str);
  }
}

// Traduz o caractere
void translate() {
  for (int i = 0; i < str.length(); i++) {
    char charact = toLowerCase(str.charAt(i));

    switch(charact) {
      case 'a':
        dot();
        dash();
        break;
      case 'b':
        dash();
        dot();
        dot();
        dot();
        break;
      case 'c':
        dash();
        dot();
        dash();
        dot();
        break;
      case 'd':
        dash();
        dot();
        dot();
        break;
      case 'e':
        dot();
        break;
      case 'f':
        dot();
        dot();
        dash();
        dot();
        break;
      case 'g':
        dash();
        dash();
        dot();
        break;
      case 'h':
        dot();
        dot();
        dot();
        dot();
        break;
      case 'i':
        dot();
        dot();
        break;
      case 'j':
        dot();
        dash();
        dash();
        dash();
        break;
      case 'k':
        dash();
        dot();
        dash();
        break;
      case 'l':
        dot();
        dash();
        dot();
        dot();
        break;
      case 'm':
        dash();
        dash();
        break;
      case 'n':
        dash();
        dot();
        break;
      case 'o':
        dash();
        dash();
        dash();
        break;
      case 'p':
        dot();
        dash();
        dash();
        dot();
        break;
      case 'q':
        dash();
        dash();
        dot();
        dash();
        break;
      case 'r':
        dash();
        dot();
        dash();
        break;
      case 's':
        dot();
        dot();
        dot();
        break;
      case 't':
        dash();
        break;
      case 'u':
        dot();
        dot();
        dash();
        break;
      case 'v':
        dot();
        dot();
        dot();
        dash();
        break;
      case 'w':
        dot();
        dash();
        dash();
        break;
      case 'x':
        dash();
        dot();
        dot();
        dash();
        break;
      case 'y':
        dash();
        dot();
        dash();
        dash();
        break;
      case 'z':
        dash();
        dash();
        dot();
        dot();
        break;
      default:
      Serial.println("Invalid charactere!");
      break;
    }
  
    if (i <= str.length() - 1) {
      delay(600); //Delay entre caracteres
    }

    status = true;
  }
}


// Pisca o LED
void dot() {
  buzzerDot();
  digitalWrite(LED, HIGH);
  delay(200);
  Serial.println(".");
  digitalWrite(LED, LOW);
  delay(200);
}

void dash() {
  buzzerDash();
  digitalWrite(LED, HIGH);
  delay(600);
  Serial.println("-");
  digitalWrite(LED, LOW);
  delay(200); 
}

// Buzzer faz bip
void buzzerDot() {
  tone(BUZZER, 440);
  delay(150);
  noTone(BUZZER);
}

void buzzerDash() {
  tone(BUZZER, 400);
  delay(600);
  noTone(BUZZER);
}
