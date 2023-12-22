# Pong

Introdução:

Recriação do jogo Pong, utilizando uma placa de led 8x8 como tela e sensores ultrassonicos de distancia como controle das raquetes.

Materiais Utilizados:
Arduino UNO
(2) Sensor de Distância Ultrassônico HC-SR04
Matriz Flexivél Endereçável Digital 64led Rgb 8x8 5v Ws2812b

Ideia projeto final:
Classico Jogo pong com modos de jogo de 1 jogador, contra a maquina ou dois jogadores, podendo escolher o modo de jogo.



Estrutura de montagem do arduino (https://wokwi.com/projects/384594518400488449):
![image](https://github.com/Jalmijao/Pong/assets/80426140/72c886d5-7478-46bd-9258-5ef5b6f6c695)

Vídeo funcionamento um jogador:
https://drive.google.com/file/d/1WMReQyKVx7VTxaWuL7fP_MzFx_e4MREj/view?usp=sharing

Vídeo funcionamento contra a maquina:
https://drive.google.com/file/d/1caEEGXffej7BTFmQAfNX9rBDiF2xztXz/view?usp=sharing

Vídeo funcionamento em dois jogadores:
https://drive.google.com/file/d/1OEXSuy2zyRCepjwLRA4VMFbTpAX5XULy/view?usp=sharing

Vídeo funcionamento troca de modos de jogo:
https://drive.google.com/file/d/1TKpW4ybSC6xDZAd7XIkeeMF5UkIip1qx/view?usp=sharing

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


15/12/2023
Alterando para novo arduino UNO
Criação do modo contra maquina
Poder alterar o modo de jogo através de um botão (único jogador contra a parede, jogador contra maquina e jogador contra jogador)


Video funcionamento dois jogadores:





