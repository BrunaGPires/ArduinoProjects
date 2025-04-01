#include <Servo.h>
Servo servo;
int posServo;

// LDR (light) Sensor
int sensLightPin = A1;
int sensLightPin2 = A2;

void setup() {
  Serial.begin(9600);
  servo.attach(3);
  pinMode(sensLightPin, INPUT);
  pinMode(sensLightPin2, INPUT);
}

void loop() {  
  int sensLight = analogRead(sensLightPin);
  int sensLight2 = analogRead(sensLightPin2);

  int posServo = map(sensLight - sensLight2, -1023, 1023, 0, 180);
  posServo = constrain(posServo, 0, 180);

  servo.write(posServo);
  
  Serial.print(" angulo servo: ");
  Serial.println(posServo);
  
  delay(1000);
  
  /*Serial.print("Luz:");
  Serial.println(sensLight);
  

  Serial.print("Luz2:");
  Serial.println(sensLight2);*/
  
}
