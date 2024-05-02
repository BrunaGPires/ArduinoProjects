#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int sensor = 0;
int sensor_pin = A0;
int led_pin = 8;

int threshold = 500;

void setup()
{
  Serial.begin(9600);
  
  pinMode(led_pin, OUTPUT);
  pinMode(sensor_pin, INPUT);
  
  //seta o numero de colunas e linhas do LCD
  lcd.begin(16, 2);
}

void loop()
{  
  sensor = analogRead(sensor_pin);
  Serial.print ("Claridade: ");
  Serial.println(sensor);
  delay (1000);
  
  if (sensor < threshold)
  {
    digitalWrite(led_pin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Dia");
    delay (500);
  }
  else
  {
    digitalWrite(led_pin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Noite");
    delay (500);
  }
  lcd.clear();
}