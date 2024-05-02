#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int motor = 0;
int sensor = 0;
int power_pin = 8; //altera sensor para on & off
int motor_pin = 9;
int sensor_pin = A0;
int thresh = 500; //valor de limite e referencia para determinar se o solo esta umido o suficiente ou não

//coraçao
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

//cara triste
byte frownie[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b00000,
  0b01110,
  0b10001
};


void setup()
{
  Serial.begin(9600);
  
  pinMode(power_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(motor_pin, OUTPUT);
  
  lcd.createChar(0, heart);
  lcd.createChar(2, frownie);
  
  lcd.begin(16, 2);
}

void loop()
{
  
  digitalWrite(power_pin, HIGH); //sensor do solo ON
  delay(10);
  sensor = analogRead(A0); //le valores do sensor
  digitalWrite(power_pin, LOW); //sensor do solo OFF
  //Serial.println(sensor); //mostra valores do sensor no monitor serial

  //se valor do sensor for maior que o valor de referencia o solo esta umido o suficiente
  if(sensor > thresh)
  {
    lcd.print("estou bem");
    lcd.write(byte(0));
    delay(1000);
    lcd.clear();
    digitalWrite(motor_pin, LOW); //motor PARA de bombear água
  }
  else
  {
    lcd.print("quero agua");
    lcd.write(byte(2));
    delay(1000);
    lcd.clear();
    digitalWrite(motor_pin, HIGH); //motor COMEÇA a bombear agua
  }
  
  delay(1000); //wait next turn
}
