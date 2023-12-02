# Pong

Introdução:

Recriação do jogo Pong, utilizando uma placa de led 8x8 como tela e sensores ultrassonicos de distancia como controle.

Materiais Utilizados:
Arduino UNO
Sensor de Distância Ultrassônico HC-SR04
Matriz Flexivél Endereçável Digital 64led Rgb 8x8 5v Ws2812b

Ideia projeto final:
Jogo pong para 1 ou dois jogadores, com uma tela inicial para escolher a dificuldade e quantidade de jogadores.


12/11/2023
![video funcionamento](https://github.com/Jalmijao/Pong/blob/main/conteudo%2012-11-2023/Funcionamento%20jogo%201%20player.mp4)


![setup inicial](https://github.com/Jalmijao/Pong/blob/main/conteudo%2012-11-2023/Setup%20inicial.png)

Jogo funcionando para único player, salvando a quantidade de pontos sofrida pelo jogador e apresentando essa informação na tela a cada ponto.
Ao levar 8 pontos o jogo é resetado.

17/10/2023
Melhora do código e otimização dos controles da raquete

24/11/2023
Criação da possibilidade de jogar em dois jogadores e criação de sistema de pontos que é mostrado na tela para cada jogador. Caso um jogador chegue a 8 pontos o jogo reinicia

01/12/2023
otimização do controle da raquete através de um novo método para acender leds sem usar delay, fonte utilizada:
https://docs.arduino.cc/built-in-examples/digital/BlinkWithoutDelay

Dessa nova forma a raquete e a bolinha nao precisam se mover na mesma velocidade, podendo alterar a velocidade da bolinha mantendo a velocidade da raquete, vice e versa




