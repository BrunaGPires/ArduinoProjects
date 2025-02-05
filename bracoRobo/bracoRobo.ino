#include <Servo.h>

#define angulo_inicial_motor 90

// Mapeamento dos botões
static const int botaoBaseEsquerda = 2;  // Botão para mover a base para a esquerda
static const int botaoBaseDireita = 3;   // Botão para mover a base para a direita
static const int botaoBraco1Cima = 4;    // Botão para mover o braço 1 para cima
static const int botaoBraco1Baixo = 7;   // Botão para mover o braço 1 para baixo
static const int botaoBraco2Cima = 8;    // Botão para mover o braço 2 para cima
static const int botaoBraco2Baixo = 9;   // Botão para mover o braço 2 para baixo
static const int botaoGarraAbrir = 12;   // Botão para abrir a garra
static const int botaoGarraFechar = 13;  // Botão para fechar a garra

// Variáveis para armazenar os ângulos atuais dos servos
int anguloBase = angulo_inicial_motor;
int anguloBraco1 = angulo_inicial_motor;
int anguloBraco2 = angulo_inicial_motor;
int anguloGarra = angulo_inicial_motor;

// Mapeamento dos servos motores
Servo motorBase;
Servo motorBraco1;
Servo motorBraco2;
Servo motorGarra;

void setup() {
  mapearPinosMotores();
  inicializaAngulosMotores();
  mapearPinosBotoes();
}

void loop() {
  moverBase();
  moverBraco1();
  moverBraco2();
  moverGarra();
}

// Funções
// Mapeia pinos dos servos motores
void mapearPinosMotores() {
  motorBase.attach(5);
  motorBraco1.attach(6);
  motorBraco2.attach(10);
  motorGarra.attach(11);
}

// Inicializa ângulos dos servos motores
void inicializaAngulosMotores() {
  motorBase.write(anguloBase);
  motorBraco1.write(anguloBraco1);
  motorBraco2.write(anguloBraco2);
  motorGarra.write(anguloGarra);
}

// Mapeia pinos dos botões como input
void mapearPinosBotoes() {
  pinMode(botaoBaseEsquerda, INPUT);
  pinMode(botaoBaseDireita, INPUT);
  pinMode(botaoBraco1Cima, INPUT);
  pinMode(botaoBraco1Baixo, INPUT);
  pinMode(botaoBraco2Cima, INPUT);
  pinMode(botaoBraco2Baixo, INPUT);
  pinMode(botaoGarraAbrir, INPUT);
  pinMode(botaoGarraFechar, INPUT);
}

// Move a base
void moverBase() {
  if (digitalRead(botaoBaseEsquerda) == HIGH) {
    anguloBase = max(anguloBase - 1, 0);  // Decrementa o ângulo, mas não menos que 0
    motorBase.write(anguloBase);
    delay(15);  // Pequeno delay para suavizar o movimento
  }
  if (digitalRead(botaoBaseDireita) == HIGH) {
    anguloBase = min(anguloBase + 1, 180);  // Incrementa o ângulo, mas não mais que 180
    motorBase.write(anguloBase);
    delay(15);
  }
}

// Move o braço 1
void moverBraco1() {
  if (digitalRead(botaoBraco1Cima) == HIGH) {
    anguloBraco1 = max(anguloBraco1 - 1, 0);
    motorBraco1.write(anguloBraco1);
    delay(15);
  }
  if (digitalRead(botaoBraco1Baixo) == HIGH) {
    anguloBraco1 = min(anguloBraco1 + 1, 180);
    motorBraco1.write(anguloBraco1);
    delay(15);
  }
}

// Move o braço 2
void moverBraco2() {
  if (digitalRead(botaoBraco2Cima) == HIGH) {
    anguloBraco2 = max(anguloBraco2 - 1, 0);
    motorBraco2.write(anguloBraco2);
    delay(15);
  }
  if (digitalRead(botaoBraco2Baixo) == HIGH) {
    anguloBraco2 = min(anguloBraco2 + 1, 180);
    motorBraco2.write(anguloBraco2);
    delay(15);
  }
}

// Move a garra
void moverGarra() {
  if (digitalRead(botaoGarraAbrir) == HIGH) {
    anguloGarra = max(anguloGarra - 1, 0);
    motorGarra.write(anguloGarra);
    delay(15);
  }
  if (digitalRead(botaoGarraFechar) == HIGH) {
    anguloGarra = min(anguloGarra + 1, 180);
    motorGarra.write(anguloGarra);
    delay(15);
  }
}