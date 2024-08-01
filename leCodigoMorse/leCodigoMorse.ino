//definindo pino do sensor
#define sensorSom A0
#define led 2

//armazena valor do sensor
int sensorValue = 0;

unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long duration = 0;

void setup() {
  Serial.begin(9600);

  pinMode(sensorSom, INPUT);
  pinMode(led, OUTPUT);
  
}

void loop() {
  receive();
}

void receive() {
  sensorValue = analogRead(sensorSom);

  Serial.print("antes do if: ");
  Serial.println(sensorValue);
  
  if (sensorValue == 1) {
     digitalWrite(led, HIGH);
     Serial.println(sensorValue);
  }
  else {
    digitalWrite(led, LOW);
  }

}
