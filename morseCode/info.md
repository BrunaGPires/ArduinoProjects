# Morse Code Sender & Receiver

- O ESP recebe uma palavra e a converte em código Morse; o som é transmitido pelo buzzer e um LED pisca de acordo com o código Morse.
- O Arduino possui um sensor de som que capta o código Morse emitido pelo buzzer e exibe o código recebido no monitor serial.
- Pretendo adicionar uma funcionalidade ao Arduino para interpretar o código Morse recebido do buzzer, traduzindo-o em palavras e exibindo-as no monitor serial.

## Components
- 1 Arduino UNO
- 1 ESP8266
- 1 Sound sensor
- 1 Buzzer
- 1 LED
- 1 LCD display

## Funcionamento
### Morse Code Sender - ESP8266
- O ESP8266 se conecta à rede local através do Wi-Fi e, em seguida, ao broker MQTT.
- O usuário pode se inscrever nos tópicos MQTT definidos (esp8266/led e esp8266/morse).
- No tópico esp8266/morse, o ESP recebe uma string, converte-a em código Morse e a transmite via buzzer e LED.
  - O buzzer emite bips curtos e longos para representar os sinais de pontos e traços, respectivamente.
  - O LED também pisca de acordo com o código Morse.
### Morse Code Receiver - Arduino UNO
- O Arduino utiliza um sensor de som para detectar os bips do buzzer do ESP.
- Quando o sensor de som detecta um nível de som acima de um limiar definido, o Arduino registra o tempo de início do som.
- Ao finalizar a detecção do som, ele calcula a duração e determina se o sinal recebido é um ponto (.) ou um traço (-), com base na duração do som.
- Cada símbolo detectado (ponto ou traço) é impresso no monitor serial e exibido em um display LCD, permitindo a visualização do código Morse recebido.
- O Arduino continua a escanear o sensor de som em loop, prontamente respondendo a novos sinais de código Morse.

https://github.com/user-attachments/assets/762c9cbb-6758-43ab-8af2-c617c9cf4367

