# PONG

## Componentes
- 1 Display OLED
- 1 Arduino UNO
- 2 Joystick Shield Nokia 5110 V2.0



## Explicação
Primeiro procurei entender como desenhar os jogadores na tela, separando a tela e colocando eles na meia metade do display e, depois, foi feito um teste de quais valores eram recebidos do joystick ao mover no eixo vertical para cima e para baixo, após ter entendido os valores que recebia do joystick era hora de receber os valores e caso passasse de um valor limite era somado a posição do jogador +1 ou -1 dependendo se era pra subir ou descer. Dessa forma conseguimos ler os valores do eixo vertical dos joysticks e os converter como movimentos dos jogadores na tela.

Para a programação da bola do jogo foi primeiramente necessário calcular a posição da bola, somando a direção da bola e à posição atual da bola. Essas variáveis determinam a direção e a velocidade da bola. O próximo passo era testar se a bola bateu nos limites horizontais da tela e fazer com que ela fosse em outra direção, para isso foi feito um if que verifica se a bola atingiu a parte superior ou inferior da tela (0 para o topo e 63 para a parte inferior, já que a altura da tela é 64 pixels). Se a bola atingir uma dessas paredes a direção da bola no eixo Y é invertida. Por final a verificação de colisão com alguma parede vertical. Verificando se a bola atingiu a borda da tela (0 para a esquerda e 127 para a direita, já que a tela tem 128 pixels de largura). Se a bola atingir a borda, então, a pontuação do jogador é incrementada, a tela é limpa, a bola é resetada para o centro da tela, a direção da bola no eixo X é invertida, fazendo com que a bola volte em direção oposta.