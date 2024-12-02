// Y VERTICAL
// X HORIZONTAL

//https://majicdesigns.github.io/MD_MAX72XX/
//https://www.farnell.com/datasheets/29075.pdf
//https://www.circuitgeeks.com/arduino-max7219-led-matrix-display/

#include <MD_MAX72xx.h>
#include <SPI.h>
#include "pitches.h"

// LED
#define MAX_DEVICES 1
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

// joystick
#define VERT_PIN A1
#define HORZ_PIN A0
#define SEL_PIN 2

// estilo, pin (low) transfere data, quantidade de led dot matrix
MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::PAROLA_HW, CS_PIN, MAX_DEVICES);

// cobrinha
const int maxX = MAX_DEVICES * 8 - 1;
const int maxY = 7;
int x = MAX_DEVICES * 8 / 2;
int y = 7 / 2;
int lastX = 0; // ultima posição X da cobrinha
int lastY = 0; // ultima posição Y da cobrinha

int cobraTamanho = 2; // tamanho inicial da cobrinha (incluindo a cabeça dela)
struct Segment {
  int x;
  int y;
};
const int MAX_SEGMENTS = 10; // número máximo de segmentos da cobrinha
Segment segments[MAX_SEGMENTS]; // array para armazenar os segmentos da cobrinha

unsigned long ultimoMovimento = 0;
const unsigned long intervaloMovimento = 400; // intervalo de movimento em milissegundos
int directionX = 1; // direção inicial da cobrinha: direita
int directionY = 0; // direção inicial da cobrinha: embaixo

// maçã
const int maxAppleX = MAX_DEVICES * 8 - 1;
const int maxAppleY = 7;
int appleX = MAX_DEVICES * 8 / 2;
int appleY = 7 / 2;
int lastAppleX = 0; // ultima posição X da maçã
int lastAppleY = 0; // ultima posição Y da maçã

// buzzer
int buzzer = 3;

void setup() {
  mx.begin();
  // acende o LED
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.clear();

  // joystick
  pinMode(VERT_PIN, INPUT);
  pinMode(HORZ_PIN, INPUT);
  pinMode(SEL_PIN, INPUT_PULLUP);

   // posição aleatoria da maçã
  randomSeed(analogRead(A5));
  sorteia(); // sorteia a posição inicial da maçã
}

void loop() {
  unsigned long currentTime = millis();

  // move a cobrinha automaticamente
  if (currentTime - ultimoMovimento >= intervaloMovimento) {
    move(); 
    ultimoMovimento = currentTime;
  }

  controle();
  maca();
  mx.update();
  delay(100);
}


void sorteia() {
  bool ocupadaPelaCobra;
  
  do {
    appleX = random(0, maxAppleX + 1);
    appleY = random(0, maxAppleY + 1);
    
    // verifica se a posição da maçã não está ocupada pela cobrinha
    ocupadaPelaCobra = false;
    for (int i = 0; i < cobraTamanho; i++) {
      if (segments[i].x == appleX && segments[i].y == appleY) {
        ocupadaPelaCobra = true;
        break;
      }
    }
  } while (ocupadaPelaCobra); // continua sorteando até encontrar uma posição valida
}

void maca() {
  mx.setPoint(appleY, appleX, true);
}

void come() {
  // desliga o LED na última posição da cobrinha
  mx.setPoint(lastY, lastX, false);
  
  // atualiza a posição da cobrinha
  lastX = x;
  lastY = y;

  // desloca todos os segmentos da cobrinha
  for (int i = cobraTamanho - 1; i > 0; i--) {
    segments[i] = segments[i - 1];
  }
  // atualiza a posição da cabeça da cobrinha
  segments[0].x = x;
  segments[0].y = y;
  
  // atualiza a posição da cauda da cobrinha (último segmento)
  lastX = segments[cobraTamanho - 1].x;
  lastY = segments[cobraTamanho - 1].y;

  // verifica se a cobrinha comeu a maçã
  if (x == appleX && y == appleY) {
    sorteia(); // sorteia uma nova posição para a maçã
    cobraTamanho++;
  }

  // verifica se a cobrinha bateu em si mesma - GAME OVER
  for (int i = 1; i < cobraTamanho; i++) {
    if (segments[i].x == x && segments[i].y == y) {
      gameOver(); // se teve colisão chama a função de game over
    }
  }

  // verifica se a cobrinha atingiu o tamanho esperado GAME WIN
  if (cobraTamanho == MAX_SEGMENTS) {
    gameWin();
  }

  // verifica se a cobrinha bateu nas paredes
  if (x < 0 || x > maxX || y < 0 || y > maxY) {
    gameOver();
  }

  mx.setPoint(y, x, true);
}

void controle() {
  int horz = analogRead(HORZ_PIN);
  int vert = analogRead(VERT_PIN);

  if (vert < 300 && directionY >= 0) {
    directionY = 1;
    directionX = 0; // garante que a cobrinha se mova apenas na vertical cima quando o comando de subir é acionado
  }
  if (vert > 700 && directionY <= 0) {
    directionY = -1;
    directionX = 0; // garante que a cobrinha se mova apenas na vertical baixo quando o comando de descer é acionado
  }
  if (horz > 700 && directionX <= 0) {
    directionX = 1;
    directionY = 0; // garante que a cobrinha se mova apenas na horizontal para direita quando o comando de ir para a direita é acionado
  }
  if (horz < 300 && directionX >= 0) {
    directionX = -1;
    directionY = 0; // garante que a cobrinha se mova apenas na horizontal para esquerda quando o comando de ir para a esquerda é acionado
  }
}

void move() {
  x = constrain(x + directionX, 0, maxX);
  y = constrain(y + directionY, 0, maxY);
  
  come();
}

void reset() {
  // reseta cobrinha 
  if (digitalRead(SEL_PIN) == LOW) {
    mx.clear();
    // reinicia todas as variaveis, a posição da cobrinha, o tamanho e a maçã
    x = MAX_DEVICES * 8 / 2;
    y = 7 / 2;
    lastX = 0;
    lastY = 0;
    appleX = MAX_DEVICES * 8 / 2;
    appleY = 7 / 2;
    lastAppleX = 0;
    lastAppleY = 0;
    cobraTamanho = 2;
  }
}

void gameOver() {
  soundLose();

  while (digitalRead(SEL_PIN) == HIGH) {
    byte sad[8] = {0x7e, 0x81, 0xa5, 0x81, 0xbd, 0xc3, 0x81, 0x7e};
  
    for (int i = 0; i < 8; i++) {
      mx.setColumn(i, sad[i]);
    }
  }

  reset();
}

void gameWin() {
  soundWin();

  while(digitalRead(SEL_PIN) == HIGH) {
    byte smile[8] = {0x7e, 0x81, 0xa5, 0x81, 0xc3, 0xbd, 0x81, 0x7e};
  
    for (int i = 0; i < 8; i++) {
      mx.setColumn(i, smile[i]); 
    }
    
  }

  reset();
}

void soundLose() {
  tone (buzzer, 125, 100);
  delay(150);
  tone (buzzer, 125, 100);
}

void soundWin() {
  tone (buzzer, 1000, 100);
  delay (150);
  tone (buzzer, 1250, 100);
}