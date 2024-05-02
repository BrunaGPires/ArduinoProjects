int fowardPin = 8;
int backwardPin = 12;

int btnOnePin = 2;
int btnTwoPin = 3;
int btnOne;
int btnTwo;

void setup()
{
  pinMode(fowardPin, OUTPUT);
  pinMode(backwardPin, OUTPUT);
  pinMode(btnOnePin, INPUT_PULLUP);
  pinMode(btnTwoPin, INPUT_PULLUP);
}

void loop()
{
  btnOne = digitalRead(btnOnePin);
  btnTwo = digitalRead(btnTwoPin);
  
  if(btnOne == HIGH)
  {
    digitalWrite(fowardPin, LOW);
  }
  else 
  {
    digitalWrite(fowardPin, HIGH);
  }
  
  if(btnTwo == HIGH)
  {
    digitalWrite(backwardPin, LOW);
  }
  else
  {
    digitalWrite(backwardPin, HIGH);
  }
}