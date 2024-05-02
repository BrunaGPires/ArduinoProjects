#include <Servo.h>

boolean __ardublockDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

Servo servo_pin_10;
int _ABVAR_1_sensor = 0 ;
int ardublockUltrasonicSensorCodeAutoGeneratedReturnCM(int trigPin, int echoPin)
{
  long duration;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  duration = duration / 59;
  if ((duration < 2) || (duration > 300)) return false;
  return duration;
}

int _ABVAR_2_direira = 0 ;
int _ABVAR_3_esquerda = 0 ;

void piscaLedRe();
void frente();
void re();
void desvia();
void parar();
void esquerda();
void direita();

void setup()
{
  servo_pin_10.attach(10);
  digitalWrite( 12 , LOW );

  Serial.begin(9600);
}

void loop()
{
  if (( ( __ardublockDigitalRead(A3) ) == ( true ) ))
  {
    analogWrite(5 , 0);
    __ardublockDigitalWrite(4, LOW);
    __ardublockDigitalWrite(3, LOW);
    analogWrite(6 , 0);
    __ardublockDigitalWrite(7, LOW);
    __ardublockDigitalWrite(8, LOW);
    __ardublockDigitalWrite(A5 , LOW);
    __ardublockDigitalWrite(2, LOW);
  }
  else
  {
    servo_pin_10.write( 90 );
    delay( 500 );
    _ABVAR_1_sensor = 	ardublockUltrasonicSensorCodeAutoGeneratedReturnCM( 12 , 11 ) ;
    Serial.print("Distancia");
    Serial.print(" ");
    Serial.println();
    Serial.print(_ABVAR_1_sensor);
    Serial.print(" ");
    Serial.println();
    delay( 100 );
    if (( ( _ABVAR_1_sensor ) < ( 10 ) ))
    {
      desvia();
    }
    else
    {
      frente();
    }
  }
}

void piscaLedRe()
{
  __ardublockDigitalWrite(2, HIGH);
  __ardublockDigitalWrite(A5 , HIGH);
  delay( 500 );
  __ardublockDigitalWrite(2, LOW);
  __ardublockDigitalWrite(A5 , LOW);
  delay( 500 );
}

void re()
{
  analogWrite(5 , 255);
  __ardublockDigitalWrite(4, LOW);
  __ardublockDigitalWrite(3, HIGH);
  analogWrite(6 , 255);
  __ardublockDigitalWrite(7, LOW);
  __ardublockDigitalWrite(8, HIGH);
  piscaLedRe();
}

void esquerda()
{
  __ardublockDigitalWrite(2, LOW);
  __ardublockDigitalWrite(A5 , HIGH);
  analogWrite(6 , 0);
  __ardublockDigitalWrite(7, LOW);
  __ardublockDigitalWrite(8, LOW);
  analogWrite(5 , 255);
  __ardublockDigitalWrite(4, HIGH);
  __ardublockDigitalWrite(3, LOW);
}

void direita()
{
  __ardublockDigitalWrite(A5 , LOW);
  __ardublockDigitalWrite(2, HIGH);
  analogWrite(5 , 0);
  __ardublockDigitalWrite(4, LOW);
  __ardublockDigitalWrite(3, LOW);
  analogWrite(6 , 255);
  __ardublockDigitalWrite(7, HIGH);
  __ardublockDigitalWrite(8, LOW);
}

void desvia()
{
  parar();
  delay( 500 );
  servo_pin_10.write( 0 );
  _ABVAR_2_direira = 	ardublockUltrasonicSensorCodeAutoGeneratedReturnCM( 12 , 11 ) ;
  delay( 1000 );
  servo_pin_10.write( 180 );
  delay( 1000 );
  _ABVAR_3_esquerda = 	ardublockUltrasonicSensorCodeAutoGeneratedReturnCM( 12 , 11 ) ;
  delay( 1000 );
  servo_pin_10.write( 90 );
  if (( ( _ABVAR_3_esquerda ) > ( 17 ) ))
  {
    esquerda();
    delay( 500 );
  }
  else
  {
    direita();
    delay( 500 );
  }
}

void frente()
{
  analogWrite(5 , 255);
  __ardublockDigitalWrite(4, HIGH);
  __ardublockDigitalWrite(3, LOW);
  analogWrite(6 , 255);
  __ardublockDigitalWrite(7, HIGH);
  __ardublockDigitalWrite(8, LOW);
  __ardublockDigitalWrite(2, HIGH);
  __ardublockDigitalWrite(A5 , HIGH);
}

void parar()
{
  analogWrite(5 , 0);
  __ardublockDigitalWrite(4, LOW);
  __ardublockDigitalWrite(3, LOW);
  analogWrite(6 , 0);
  __ardublockDigitalWrite(7, LOW);
  __ardublockDigitalWrite(8, LOW);
  __ardublockDigitalWrite(2, LOW);
  __ardublockDigitalWrite(A5 , LOW);
}
