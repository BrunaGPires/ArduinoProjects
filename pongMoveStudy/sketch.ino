// Y VERTICAL
// X HORIZONTAL

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definindo pin vertical dos joysticks
const int joystickOne = A0; 
const int joystickTwo = A1;

// Definindo valores da linha dos jogadores e 
// Definindo valores da posição dos jogadores
const uint8_t line_size = 12;
const unsigned long line_fps = 5;
unsigned long line_update;

const uint8_t playerOne_x = 23;
uint8_t playerOne_y = 26;

const uint8_t playerTwo_x =  105;
uint8_t playerTwo_y = 26;

int playerOneScore = 0;
int  playerTwoScore = 0;

// Definindo valores da bola e
// Defininfo valores da posição da bola
uint8_t ball_fps = 0;
unsigned long ball_update;
bool resetBall = false;

// Metade da largura da tela e metade da altura da tela
uint8_t  ball_x = 64, ball_y = 32;
uint8_t ball_dir_x = 1, ball_dir_y = 1;

int buzzer = 7;
int maxGame = 10;

// Definindo parametros do Display
#define LARGURA_OLED 128
#define ALTURA_OLED 64
#define RESET_OLED -1
Adafruit_SSD1306 display(LARGURA_OLED, ALTURA_OLED, &Wire, RESET_OLED);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  unsigned long start = millis();

  display.clearDisplay();
  drawCourt();
  drawScore();
  while  (millis() - start < 2000);

  display.display();

  ball_update = millis();
  line_update = ball_update;
}

void loop() {
  bool update = false;
  unsigned long time = millis();

  // FIM
  if (resetBall) {
    if (playerOneScore == maxGame || playerTwoScore == maxGame) {
      gameOver();
    } 
    else {
      display.fillScreen(BLACK);
      drawScore();
      drawCourt();
      ball_x = random(45, 50);
      ball_y = random(23, 33);
      do
      {
        ball_dir_x = random(-1, 2);
      } while (ball_dir_x == 0);

      do
      {
        ball_dir_y = random(-1, 2);
      } while (ball_dir_y  == 0);


      resetBall = false;
    }
  }

  // BOLA
  if (time > ball_update) {
    uint8_t new_x = ball_x + ball_dir_x;
    uint8_t new_y = ball_y + ball_dir_y;

    // Verifica se a bola foi em alguma das linhas vertical da tela
    if (new_x == 0 || new_x == 127) {

      if (new_x == 0) {
        playerOneScore += 1;
        display.fillScreen(BLACK);
        soundPoint();
        resetBall = true;

      }
      else if (new_x == 127) {
        playerTwoScore  += 1;
        display.fillScreen(BLACK);
        soundPoint();
        resetBall  = true;
      }
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x  + ball_dir_x;
    }

    // Verifica se a bola foi em alguma das linhas horizontais da tela
    if  (new_y == 0 || new_y == 63) {
      soundBounce();
      ball_dir_y = -ball_dir_y;
      new_y += ball_dir_y + ball_dir_y;
    }

    // Verifica se a bola bateu no jogador dois
    if (new_x == playerTwo_x && new_y >= playerTwo_y && new_y <=  playerTwo_y + line_size) {
      soundBounce();
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
    }

    // Verifica se a bola bateu no jogador um
    if (new_x == playerOne_x && new_y >= playerOne_y && new_y <= playerOne_y  + line_size) {
      soundBounce();
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
    }

    display.drawPixel(ball_x,  ball_y, BLACK);
    display.drawPixel(new_x, new_y, WHITE);
    ball_x = new_x;
    ball_y = new_y;

    ball_update += ball_fps;

    update = true;
  }

  // JOGADORES
  if (time > line_update) {
    line_update += line_fps;

    // Desenha e atualiza player UM
    display.drawFastVLine(playerOne_x, playerOne_y, line_size, BLACK);

    if (analogRead(joystickOne) < 475) {
      playerOne_y += 1;
    }
    if (analogRead(joystickOne) > 550) {
      playerOne_y -= 1;
    }

    if (playerOne_y < 1) playerOne_y = 1;
    if (playerOne_y + line_size > 63) playerOne_y = 63 - line_size;
    display.drawFastVLine(playerOne_x, playerOne_y, line_size, WHITE);

    // Desenha e atualiza player DOIS
    display.drawFastVLine(playerTwo_x, playerTwo_y, line_size, BLACK);

    if (analogRead(joystickTwo) < 475) {
      playerTwo_y += 1;
    }
    if (analogRead(joystickTwo) > 550) {
      playerTwo_y -= 1;
    }

    if (playerTwo_y < 1) playerTwo_y = 1;
    if (playerTwo_y + line_size > 63) playerTwo_y = 63 - line_size;
    display.drawFastVLine(playerTwo_x, playerTwo_y, line_size, WHITE);
  }

  update = true;

  if (update) {
    drawScore();
    display.display();
  }

}

void drawCourt() {
  display.drawRect(0,  0, 128, 64, WHITE);
}

void drawScore() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(45, 2);
  display.println(playerTwoScore);
  display.setCursor(75, 2);
  display.println(playerOneScore);
}

void  gameOver() { 
  display.fillScreen(BLACK);

  if (playerOneScore > playerTwoScore)
  {
    display.setCursor(20, 15);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.print("Player 1");
    display.setCursor(40, 35);
    display.print("won");
  }
  else
  {
    display.setCursor(20, 15);
    display.setTextColor(WHITE);
    display.setTextSize(2);
    display.print("Player 2");
    display.setCursor(40,  35);
    display.print("won");
  }

  delay(100);
  display.display();
  delay(2000);
  playerTwoScore = playerOneScore = 0;

  unsigned long start  = millis();
  while (millis() - start < 2000);
  ball_update = millis();
  line_update = ball_update;
  resetBall = true;
}

// Som da bola quando vai em alguma parede
void soundBounce()
{
  tone(buzzer, 500, 50);
}
// Som de ponto feito
void soundPoint()
{
  tone(buzzer, 100, 50);
}