// C++ code
//
int led_red = 2;
int led_yellow = 3;
int led_green = 4;

int btn = 5;
int btnState = 0;

void setup()
{
  pinMode(led_red, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(btn, INPUT);
}

void loop()
{
  btnState = digitalRead(5);
  
  if (btnState == LOW) {
    digitalWrite(led_green, HIGH);
  }
  
  if(btnState == HIGH) {
    delay(1000);
    digitalWrite(led_green, LOW);
    delay(100);
    
    digitalWrite(led_yellow, HIGH);
    delay(2000);
    digitalWrite(led_yellow, LOW);
    delay(100);

    digitalWrite(led_red, HIGH);
    delay(5000);
    digitalWrite(led_red, LOW);
    delay(100);
  }
}