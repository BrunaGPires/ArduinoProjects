#define ENB 6 //PWM
#define IN3 7
#define IN4 8

void setup() {
  Serial.begin(9600);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  //digitalWrite(IN3, LOW);
  //digitalWrite(IN4, LOW);
  //analogWrite(ENB, 0);
}

void loop() {
  // motores para frente
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  acelera();
  naoAcelera();

  delay(500);
  
  //motores para trás
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  acelera();
  naoAcelera();

  delay(500);

  //motores para trás full speed
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENB, 255);

  delay(1500);

  analogWrite(ENB, 0);

  delay(500);
}

void acelera() {
  for (int i = 0; i < 255; i++) {
    analogWrite(ENB, i);
    delay(20);
  }
}

void naoAcelera() {
  for (int i = 255; i > 0; --i) {
    analogWrite(ENB, i);
    delay(20);
  }
}
