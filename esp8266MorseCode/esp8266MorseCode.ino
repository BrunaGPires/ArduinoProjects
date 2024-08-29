#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Preencha abaixo as informacoes da sua rede Wifi
const char* ssid = "PMNH-LIVRE";
const char* password = "";
const char* mqtt_server = "mqtt.eclipseprojects.io"; // Endereco do Broker MQTT

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

// Variaveis morse
#define LED D1
#define BUZZER D2
String str = "";
bool status = false;

// Tópico para controlar o LED
const char* ledTopic = "esp8266/led";
const char* morseTopic = "esp8266/morse";

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereco IP: ");
  Serial.println(WiFi.localIP());
}

//pisca o led
void dot() {
  buzzerDot();
  digitalWrite(LED, HIGH);
  delay(110);
  Serial.println(".");
  digitalWrite(LED, LOW);
  delay(200);
}

void dash() {
  buzzerDash();
  digitalWrite(LED, HIGH);
  delay(300);
  Serial.println("-");
  digitalWrite(LED, LOW);
  delay(200); 
}

//buzer bipbip
void buzzerDot() {
  tone(BUZZER, 440);
  delay(110);
  noTone(BUZZER);
}

void buzzerDash() {
  tone(BUZZER, 400);
  delay(300);
  noTone(BUZZER);
}

void translateMorseCode(String message) {
  for (int i = 0; i < message.length(); i++) {
    char charact = toLowerCase(message.charAt(i));

    switch(charact) {
      case 'a':
        dot();
        dash();
        break;
      case 'b':
        dash();
        dot();
        dot();
        dot();
        break;
      case 'c':
        dash();
        dot();
        dash();
        dot();
        break;
      case 'd':
        dash();
        dot();
        dot();
        break;
      case 'e':
        dot();
        break;
      case 'f':
        dot();
        dot();
        dash();
        dot();
        break;
      case 'g':
        dash();
        dash();
        dot();
        break;
      case 'h':
        dot();
        dot();
        dot();
        dot();
        break;
      case 'i':
        dot();
        dot();
        break;
      case 'j':
        dot();
        dash();
        dash();
        dash();
        break;
      case 'k':
        dash();
        dot();
        dash();
        break;
      case 'l':
        dot();
        dash();
        dot();
        dot();
        break;
      case 'm':
        dash();
        dash();
        break;
      case 'n':
        dash();
        dot();
        break;
      case 'o':
        dash();
        dash();
        dash();
        break;
      case 'p':
        dot();
        dash();
        dash();
        dot();
        break;
      case 'q':
        dash();
        dash();
        dot();
        dash();
        break;
      case 'r':
        dash();
        dot();
        dash();
        break;
      case 's':
        dot();
        dot();
        dot();
        break;
      case 't':
        dash();
        break;
      case 'u':
        dot();
        dot();
        dash();
        break;
      case 'v':
        dot();
        dot();
        dot();
        dash();
        break;
      case 'w':
        dot();
        dash();
        dash();
        break;
      case 'x':
        dash();
        dot();
        dot();
        dash();
        break;
      case 'y':
        dash();
        dot();
        dash();
        dash();
        break;
      case 'z':
        dash();
        dash();
        dot();
        dot();
        break;
      case ' ':
        delay(360);
      default:
      Serial.println("Invalid charactere!");
      break;
    }

    if (i <= message.length() - 1) {
      delay(300);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (String(topic) == ledTopic) {
    if (message == "ON") {
      digitalWrite(LED, HIGH); // Ligar LED
      Serial.println("LED ligado");
    } else if (message == "OFF") {
      digitalWrite(LED, LOW); // Desligar LED
      Serial.println("LED desligado");
    }
  }

  if (String(topic) == morseTopic) {  
    str = message;
    translateMorseCode(str);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexao MQTT...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
      client.subscribe(ledTopic); // Inscreve-se no tópico de controle do LED
      client.subscribe(morseTopic);
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT); 
  digitalWrite(LED, LOW); // LED desligado inicialmente

  Serial.begin(9600);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis(); 
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf(msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
  }
}
