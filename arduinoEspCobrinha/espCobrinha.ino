#include <MD_MAX72xx.h>
#include <SPI.h>

#define MAX_DEVICES 1
#define CLK_PIN D5
#define DATA_PIN D7
#define CS_PIN D3

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::PAROLA_HW, CS_PIN, MAX_DEVICES);

// cobra
const int maxX = MAX_DEVICES * 8 - 1;
const int maxY = 7;
int x = MAX_DEVICES * 8 / 2;
int y = 7 / 2;
int lastX = 0; // ultima posição X da cobra
int lastY = 0; // ultima posição Y da cobra

int cobraTamanho = 2; // tamanho inicial da cobra (incluindo a cabeça)
struct Segment {
  int x;
  int y;
};
const int MAX_SEGMENTS = 10; // número máximo de segmentos da cobra
Segment segments[MAX_SEGMENTS]; // array para armazenar os segmentos da cobra

unsigned long ultimoMovimento = 0;
const unsigned long intervaloMovimento = 500; // intervalo de movimento em milissegundos
int directionX = 1; // direção inicial da cobra: direita
int directionY = 0; // direção inicial da cobra: embaixo

// maçã
const int maxAppleX = MAX_DEVICES * 8 - 1;
const int maxAppleY = 7;
int appleX = MAX_DEVICES * 8 / 2;
int appleY = 7 / 2;
int lastAppleX = 0; // ultima posição X da maçã
int lastAppleY = 0; // ultima posição Y da maçã

// setas
#define up D2 //D2 - A
#define down D6 //D4 - C
#define right D4 //D3 - B
#define left D8 //D5 - D

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output

  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, MAX_INTENSITY / 2);
  mx.clear();

  // joystick
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  
  randomSeed(analogRead(A0));
  sorteia();
}

// the loop function runs over and over again forever
void loop() { 
  unsigned long currentTime = millis();

  // move a cobra automaticamente
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
    
    // verifica se a posição da maçã não está ocupada pela cobra
    ocupadaPelaCobra = false;
    for (int i = 0; i < cobraTamanho; i++) {
      if (segments[i].x == appleX && segments[i].y == appleY) {
        ocupadaPelaCobra = true;
        break;
      }
    }
  } while (ocupadaPelaCobra); // continua sorteando até encontrar uma posição válida
}

void maca() {
  mx.setPoint(appleY, appleX, true);
}

void come() {
  // desliga o LED na última posição da cobra
  mx.setPoint(lastY, lastX, false);
  
  // atualiza a posição da cobra
  lastX = x;
  lastY = y;

  // desloca todos os segmentos da cobra
  for (int i = cobraTamanho - 1; i > 0; i--) {
    segments[i] = segments[i - 1];
  }
  // atualiza a posição da cabeça
  segments[0].x = x;
  segments[0].y = y;
  
  // atualiza a posição da cauda (último segmento)
  lastX = segments[cobraTamanho - 1].x;
  lastY = segments[cobraTamanho - 1].y;

  // verifica se a cobra atingiu a maçã
  if (x == appleX && y == appleY) {
    sorteia(); // sorteia uma nova posição para a maçã
    cobraTamanho++;
  }

  // verifica se a cobra bateu em si mesma - GAME OVER
  for (int i = 1; i < cobraTamanho; i++) {
    if (segments[i].x == x && segments[i].y == y) {
      gameOver(); // se houver colisão, chama a função de game over
    }
  }

  // verifica se a cobra atingiu o tamanho esperado - GAME WIN
  if (cobraTamanho == MAX_SEGMENTS) {
    gameWin();
  }

  // verifica se a cobra bateu nas paredes
  if (x < 0 || x > maxX || y < 0 || y > maxY) {
    gameOver();
  }

  mx.setPoint(y, x, true);
}

void controle() {
  int upDir = digitalRead(up);
  int downDir = digitalRead(down);
  int leftDir = digitalRead(left);
  int rightDir = digitalRead(right);

  if (upDir == LOW && directionY >= 0) {
    Serial.println("UP");
    directionY = -1;
    directionX = 0; // garante que a cobra se mova apenas na vertical quando o comando de subir é acionado
  }
  if (downDir == LOW && directionY <= 0) {
    Serial.println("DOWN");
    directionY = 1;
    directionX = 0; // garante que a cobra se mova apenas na vertical quando o comando de descer é acionado
  }
  if (rightDir == LOW && directionX <= 0) {
    Serial.println("RIGHT");
    directionX = 1;
    directionY = 0; // garante que a cobra se mova apenas na horizontal quando o comando de ir para a direita é acionado
  }
  if (leftDir == LOW && directionX >= 0) {
    Serial.println("LEFT");
    directionX = -1;
    directionY = 0; // garante que a cobra se mova apenas na horizontal quando o comando de ir para a esquerda é acionado
  }
}

void move() {
  x = constrain(x + directionX, 0, maxX);
  y = constrain(y + directionY, 0, maxY);
  
  come();
}

void reset() {
  // reseta cobrinha 
    mx.clear();
    // reinicia todas as variáveis, posição da cobra, tamanho, maçã.
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

void gameOver() {
    byte sad[8] = {0x7e, 0x81, 0xa5, 0x81, 0xbd, 0xc3, 0x81, 0x7e};
  
    for (int i = 0; i < 8; i++) {
      mx.setColumn(i, sad[i]);
    }
  
  delay(5000);
  reset();
}

void gameWin() {
    byte smile[8] = {0x7e, 0x81, 0xa5, 0x81, 0xc3, 0xbd, 0x81, 0x7e};
  
    for (int i = 0; i < 8; i++) {
      mx.setColumn(i, smile[i]); 
    
    
  }
  delay(5000);

  reset();
}
