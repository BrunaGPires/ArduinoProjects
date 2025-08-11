#define ILI9341_BLACK       0x0000  ///<   0,   0,   0
#define ILI9341_NAVY        0x000F  ///<   0,   0, 123
#define ILI9341_DARKGREEN   0x03E0  ///<   0, 125,   0
#define ILI9341_DARKCYAN    0x03EF  ///<   0, 125, 123
#define ILI9341_MAROON      0x7800  ///< 123,   0,   0
#define ILI9341_PURPLE      0x780F  ///< 123,   0, 123
#define ILI9341_OLIVE       0x7BE0  ///< 123, 125,   0
#define ILI9341_LIGHTGREY   0xC618  ///< 198, 195, 198
#define ILI9341_DARKGREY    0x7BEF  ///< 123, 125, 123
#define ILI9341_BLUE        0x001F  ///<   0,   0, 255
#define ILI9341_GREEN       0x07E0  ///<   0, 255,   0
#define ILI9341_CYAN        0x07FF  ///<   0, 255, 255
#define ILI9341_RED         0xF800  ///< 255,   0,   0
#define ILI9341_MAGENTA     0xF81F  ///< 255,   0, 255
#define ILI9341_YELLOW      0xFFE0  ///< 255, 255,   0
#define ILI9341_WHITE       0xFFFF  ///< 255, 255, 255
#define ILI9341_ORANGE      0xFD20  ///< 255, 165,   0
#define ILI9341_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define ILI9341_PINK        0xFC18  ///< 255, 130, 198

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_FT6206.h"
#include "Adafruit_ILI9341.h"

#define TFT_CLK 13
#define TFT_MISO 12
#define TFT_MOSI 11
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

Adafruit_FT6206 ts = Adafruit_FT6206();

// rectangle variables
const int RECT_WIDTH = 40;
const int RECT_HEIGHT = 30;
int rectX, rectY;
bool retanguloAtivo = false;

// random colors variables
const uint16_t colors[] = {
  ILI9341_RED,
  ILI9341_BLUE,
  ILI9341_GREEN,
  ILI9341_YELLOW,
  ILI9341_ORANGE,
  ILI9341_PINK,
  ILI9341_PURPLE
};
const int NUM_COLORS = sizeof(colors) / sizeof(colors[0]);

// score
int score = 0;

void setup() {
  Serial.begin(9600);
  tft.begin();
  ts.begin();
  tft.setRotation(2);
}

void loop() {
  if(!retanguloAtivo) {
    randomRects();
  }
  touch();
  text();
  delay(20);
}

void randomRects() {
  rectX = random(0, tft.width() - RECT_WIDTH);
  rectY = random(0, tft.height() - RECT_HEIGHT);

  uint16_t selectedColor = colors[random(NUM_COLORS)];
  
  tft.fillRect(rectX, rectY, RECT_WIDTH, RECT_HEIGHT, selectedColor);
  retanguloAtivo = true;
  
  /*Serial.print("Retângulo em: ");
  Serial.print(rectX); Serial.print(", "); Serial.println(rectY);*/
}

void touch() {
  if(ts.touched()) {
    TS_Point p = ts.getPoint();
    
    /*Serial.print("Toque em: ");
    Serial.print(p.x); Serial.print(", "); Serial.println(p.y);*/

    if(p.x >= rectX && p.x <= (rectX + RECT_WIDTH) && 
       p.y >= rectY && p.y <= (rectY + RECT_HEIGHT)) {
      tft.fillRect(rectX, rectY, RECT_WIDTH, RECT_HEIGHT, ILI9341_BLACK);
      score += 1;
      retanguloAtivo = false;
      while(ts.touched()) delay(10);
    }
  }
}

void text() {
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print("SCORE: ");

  tft.setTextColor(ILI9341_YELLOW, ILI9341_BLACK);
  tft.setTextSize(1);
  tft.println(score);
  timer();
}

void timer() {
  unsigned long time = micros();

  // 1s = 1.000.000micro

  float timeInSeconds = time / 1000000.0;

  tft.setCursor(100, 0);
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  tft.setTextSize(1);
  tft.print(timeInSeconds);
}
