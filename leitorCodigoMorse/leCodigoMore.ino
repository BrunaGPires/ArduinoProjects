#include <LiquidCrystal_I2C.h>

// SOUND SENSOR
const int sensorSound = A0;

unsigned long startTimer = 0;  // variável para armazenar o tempo inicial do som
unsigned long endTimer = 0;    // variável para armazenar o tempo final do som
const int soundThreshold = 25; // referência para indicar se o som foi detectado
const unsigned long dotDuration = 120; // limite de duração para ponto (em milissegundos)

bool soundDetected = false;

// LCD DISPLAY
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
    pinMode(sensorSound, INPUT);

    lcd.init();
    lcd.backlight();
    
    Serial.begin(9600);
    Serial.println("Starting Morse Code Receiver...");
}

void loop() {
    receive();
}

void receive() {
    int sensorValue = 0;
    
    for (int i = 0; i < 32; i++) { 
        sensorValue += analogRead(sensorSound);  
    }
    sensorValue >>= 5; // bitshift operation

    if (sensorValue >= soundThreshold) { 
        if (!soundDetected) {
            startTimer = millis();
            soundDetected = true;  
        }
    } else if (soundDetected) {
      endTimer = millis();
      unsigned long soundDuration = endTimer - startTimer;
      
      if (soundDuration < dotDuration) {
        // Ponto
        Serial.println(soundDetected);
        Serial.println(".");
        
        lcd.setCursor(0, 0);
        lcd.print(".");
      } else {
        // Traço
        Serial.println(soundDetected);
        Serial.println("-");
        
        lcd.setCursor(0, 0);
        lcd.print("-");
      }
      soundDetected = false;
   }
}
