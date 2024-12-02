# SnakeGame

## Components
- 1 LED Dot Matrix 8x8
- 1 Arduino Wemos D1
- 1 Joystick Shield Nokia 5110 V2.0
- 11 Jumpers

https://github.com/BrunaGPires/ArduinoProjects/assets/99612473/569d34ac-3b8d-4e35-9c6a-5963a0043d8b

## Explicação
A parte interessante do projeto foi aprender a fazer a cobrinha se mover na matriz. A matriz de LEDs funciona de forma que cada LED é um ponto que pode estar ligado ou desligado. O joystick controla apenas a direção da cobrinha, movendo-a para cima, para baixo, para a esquerda ou para a direita, alterando assim as coordenadas X e Y da cobrinha. O movimento é restrito para evitar que a cobrinha se mova em direção ao seu próprio corpo. Por exemplo, se ela estiver indo para a esquerda e o joystick for direcionado para a direita, o movimento não será executado.

A cobrinha se move automaticamente a cada intervalo de tempo de 400 milissegundos. A cada movimento, a cabeça da cobrinha avança para a nova posição, e os segmentos do corpo a seguem na mesma direção.

Quando a cobrinha come a maçã, ela cresce, com um novo segmento sendo adicionado ao seu corpo.