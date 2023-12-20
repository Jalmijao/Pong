#include <HCSR04.h>
#include <FastLED.h>

#define NUM_LEDS 64

#define DATA_PIN 8
#define CLOCK_PIN 13

unsigned long previousMillisBolinha = 0;  

unsigned long previousMillisRaquete = 0;  

long delayBolinha = 550;  
const long delayRaquete = 200;
int pushbutton = 2; // declara o push button na porta 2
UltraSonicDistanceSensor distanceSensor(10, 9);  // Initialize sensor that uses digital pins 13 and 12.
UltraSonicDistanceSensor distanceSensor2(12, 11);  // Initialize sensor that uses digital pins 13 and 12.
int matriz[8][8];
int bolinhaY = 3;
int bolinhaX = 3;
int adicaoY = 0;
int adicaoX = 1;
int posicaoRaquete1 = 3;
int posicaoRaquete2 = 3;
int delayJogo = 350;
int pontosJogador1 = 0;
int pontosJogador2 = 0;
bool doisJogadores=true;
bool isContraMaquina=false;
bool subindo=true;
bool estadoled = 0; // variavel de controle
// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao 
  defineMatriz();
  Serial.begin(9600);
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  leds[matriz[0][posicaoRaquete1]] = CRGB::Blue;
  leds[matriz[0][posicaoRaquete1 - 1]] = CRGB::Blue;
  int randomico = random(0, 2);
  if(randomico==0){
    adicaoX=-1;
  }
  if(randomico==1){
    adicaoX=1;
  }
}
void defineMatriz() {
  int i = 0;
  int j = 0;
  while (i < 8) {
    matriz[0][j] = i;
    i++;
    j++;

  }
  j = 7;
  while (i < 16) {
    matriz[1][j] = i;
    i++;
    j--;
  }

  j = 0;
  while (i < 24) {
    matriz[2][j] = i;
    i++;
    j++;
  }
  j = 7;
  while (i < 32) {
    matriz[3][j] = i;
    i++;
    j--;
  }
  j = 0;
  while (i < 40) {
    matriz[4][j] = i;
    i++;
    j++;
  }
  j = 7;
  while (i < 48) {
    matriz[5][j] = i;
    i++;
    j--;
  }
  j = 0;
  while (i < 56) {
    matriz[6][j] = i;
    i++;
    j++;
  }
  j = 7;
  while (i < 64) {
    matriz[7][j] = i;
    i++;
    j--;
  }
}

void ReiniciaJogo() {
  delayBolinha = 550;
  pontosJogador1 = 0;
  pontosJogador2 = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[matriz[i][j]] = CRGB::DarkRed;
    }
  }
  FastLED.show();
  delay(1000);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[matriz[i][j]] = CRGB::Black;
    }
  }
  FastLED.show();

}
void colisaoParede() {
  int randomico = random(0, 3);

  if (adicaoY == 0) {
    adicaoY = 1;
  }
  if (randomico == 1) {
    adicaoY = -1;

  }
  else if (randomico == 2) {
    adicaoY = 0;

  }

  adicaoX = adicaoX * -1;

}
void colisaoChao() {
  if (adicaoY == 0) {
    adicaoY = 1;
  }
  adicaoY = adicaoY * -1;
}
void diminuiDelay() {
  if (delayBolinha > 200) {
    delayBolinha = delayBolinha - 10;
  }
}
void RandomY(){
  int randomico = random(0, 3);

    if (adicaoY == 0) {
      adicaoY = 1;
    }
    if (randomico == 1) {
      adicaoY = -1;
  
    }
    else if (randomico == 2) {
      adicaoY = 0;
  
    }
}
void colisaoRaquete1() {

  if (bolinhaX == 1 && (bolinhaY == posicaoRaquete1 || bolinhaY == posicaoRaquete1 - 1)) {
    //Serial.println("COLISAO");
    adicaoX = 1;
    RandomY();
    diminuiDelay();

  }
  else if (bolinhaX == 1 && adicaoY == -1 && bolinhaY == posicaoRaquete1 + 1) {
    //Serial.println("COLISAO");
    adicaoX = 1;
    RandomY();
    diminuiDelay();
  }
  else if (bolinhaX == 1 && adicaoY == 1 && bolinhaY == posicaoRaquete1 - 2) {
    //Serial.println("COLISAO");
    adicaoX = 1;
    RandomY();
    diminuiDelay();
  }
}
void colisaoRaquete2() {
 
  if (bolinhaX == 6 && (bolinhaY == posicaoRaquete2 || bolinhaY == posicaoRaquete2 - 1)) {
    //Serial.println("COLISAO");
    adicaoX = -1;
     RandomY();
    diminuiDelay();

  }
  else if (bolinhaX == 6 && adicaoY == -1 && bolinhaY == posicaoRaquete2 + 1) {
    //Serial.println("COLISAO");
    adicaoX = -1;
    RandomY();
    diminuiDelay();
  }
  else if (bolinhaX == 6 && adicaoY == 1 && bolinhaY == posicaoRaquete2 - 2) {
    //Serial.println("COLISAO");
    adicaoX = -1;
    RandomY();
    diminuiDelay();
  }
}
void luzesPontuacao() {
  leds[matriz[3][3]] = CRGB::DarkRed;

  FastLED.show();

  delay(200);

  leds[matriz[3][4]] = CRGB::DarkRed;
  leds[matriz[4][3]] = CRGB::DarkRed;
  leds[matriz[4][4]] = CRGB::DarkRed;
  FastLED.show();

  delay(400);


  leds[matriz[3][3]] = CRGB::Black;
  leds[matriz[3][4]] = CRGB::Black;
  leds[matriz[4][3]] = CRGB::Black;
  leds[matriz[4][4]] = CRGB::Black;
  FastLED.show();

}
void reiniciaBolinha() {
  
  
  FastLED.show();
   int randomico = random(0, 2);
  if(randomico==0){
    leds[matriz[5][3]] = CRGB::Blue;
    bolinhaX = 5;
  bolinhaY = 3;
    adicaoX=-1;
    delay(400);
    leds[matriz[5][3]] = CRGB::Black;
  }
  if(randomico==1){
    leds[matriz[2][3]] = CRGB::Blue;
    bolinhaX = 2;
  bolinhaY = 3;
    adicaoX=1;
    delay(400);
    leds[matriz[2][3]] = CRGB::Black;
  }
  
  
  adicaoY = 0;
  
    
      FastLED.show();
}
void bolinha() {


  bolinhaX = bolinhaX + adicaoX;

  bolinhaY = bolinhaY + adicaoY;

  //Serial.println(bolinhaY);
  //Serial.println(adicaoY);
  // Serial.println(adicaoX);

 

  colisaoRaquete1();
  if(doisJogadores){
     colisaoRaquete2();
  }

  if (bolinhaX == 0) {
    leds[matriz[bolinhaX][bolinhaY]] = CRGB::DarkRed;
    luzesPontuacao();
    leds[matriz[bolinhaX][bolinhaY]] = CRGB::Black;
    
    pontosJogador2 = pontosJogador2 + 1;


    for (int i = 0; i < pontosJogador2; i++) {
      leds[matriz[6][i]] = CRGB::DarkRed;
    }
    FastLED.show();
    delay(500);
    for (int i = 0; i < pontosJogador2; i++) {
      leds[matriz[6][i]] = CRGB::Black;
    }
    FastLED.show();

    if (pontosJogador1 == 8 || pontosJogador2 ==8) {
      ReiniciaJogo();

    }
    reiniciaBolinha();

  }

   if (bolinhaX == 7 && doisJogadores) {
    leds[matriz[bolinhaX][bolinhaY]] = CRGB::DarkRed;
    luzesPontuacao();
    leds[matriz[bolinhaX][bolinhaY]] = CRGB::Black;
    
    pontosJogador1 = pontosJogador1 + 1;


    for (int i = 0; i < pontosJogador1; i++) {
      leds[matriz[1][i]] = CRGB::DarkRed;
    }
    FastLED.show();
    delay(500);
    for (int i = 0; i < pontosJogador1; i++) {
      leds[matriz[1][i]] = CRGB::Black;
    }
    FastLED.show();

    if (pontosJogador1 == 8) {
      ReiniciaJogo();

    }
    reiniciaBolinha();
  }

  if (bolinhaX == 7) {
    colisaoParede();

  }


  else if (bolinhaY == 7 || bolinhaY == 0) {
    colisaoChao();
  }


}

void computaRaqueteSoma1() {
  float distancia = distanceSensor.measureDistanceCm();
  
  // Serial.println(posicaoRaquete1);
  //Serial.println(distancia);

  if (distancia < 20 ) {
    if (distancia > 10 && posicaoRaquete1 < 7) {

      leds[matriz[0][posicaoRaquete1]] = CRGB::Black;
      leds[matriz[0][posicaoRaquete1 - 1]] = CRGB::Black;

      posicaoRaquete1 = posicaoRaquete1 + 1;

      leds[matriz[0][posicaoRaquete1]] = CRGB::Blue;
      leds[matriz[0][posicaoRaquete1 - 1]] = CRGB::Blue;

      
    }
    else if (distancia < 7 && posicaoRaquete1 > 1) {

      leds[matriz[0][posicaoRaquete1]] = CRGB::Black;
      leds[matriz[0][posicaoRaquete1 - 1]] = CRGB::Black;

      posicaoRaquete1 = posicaoRaquete1 - 1;

      leds[matriz[0][posicaoRaquete1]] = CRGB::Blue;
      leds[matriz[0][posicaoRaquete1 - 1]] = CRGB::Blue;
      

    }
  
  }
}
void computaRaqueteSoma2() {
  if(isContraMaquina){
    if(bolinhaY> posicaoRaquete2){
     subindo=true;
    }
    else if(bolinhaY<posicaoRaquete2 ){
      subindo=false;
    }
    if(subindo && posicaoRaquete2<7){
       leds[matriz[7][posicaoRaquete2]] = CRGB::Black;
      leds[matriz[7][posicaoRaquete2 - 1]] = CRGB::Black;

      posicaoRaquete2 = posicaoRaquete2 + 1;

      leds[matriz[7][posicaoRaquete2]] = CRGB::Blue;
      leds[matriz[7][posicaoRaquete2 - 1]] = CRGB::Blue;
    }
    else if(posicaoRaquete2>1){
 leds[matriz[7][posicaoRaquete2]] = CRGB::Black;
      leds[matriz[7][posicaoRaquete2 - 1]] = CRGB::Black;

      posicaoRaquete2 = posicaoRaquete2 - 1;

      leds[matriz[7][posicaoRaquete2]] = CRGB::Blue;
      leds[matriz[7][posicaoRaquete2 - 1]] = CRGB::Blue;

    }
      
  }
  else{
float distancia = distanceSensor2.measureDistanceCm();

  // Serial.println(posicaoRaquete1);
  Serial.println(distancia);
     Serial.println("aaa");

  if (distancia < 20 ) {
      Serial.println("bbb");

      if (distancia > 10 && posicaoRaquete2 < 7) {

        leds[matriz[7][posicaoRaquete2]] = CRGB::Black;
        leds[matriz[7][posicaoRaquete2 - 1]] = CRGB::Black;

        posicaoRaquete2 = posicaoRaquete2 + 1;

        leds[matriz[7][posicaoRaquete2]] = CRGB::Blue;
        leds[matriz[7][posicaoRaquete2 - 1]] = CRGB::Blue;
      }
      else if (distancia < 7 && posicaoRaquete2 > 1) {

        leds[matriz[7][posicaoRaquete2]] = CRGB::Black;
        leds[matriz[7][posicaoRaquete2 - 1]] = CRGB::Black;

        posicaoRaquete2 = posicaoRaquete2 - 1;

        leds[matriz[7][posicaoRaquete2]] = CRGB::Blue;
        leds[matriz[7][posicaoRaquete2 - 1]] = CRGB::Blue;

      }

    }
  }
  
}
void ProximoModo(){
  if(!doisJogadores){
    doisJogadores=true;
  }
  else if(doisJogadores && !isContraMaquina){
    isContraMaquina=true;
  }
  else if(isContraMaquina){
    isContraMaquina=false;
    doisJogadores=false;
  }
}
void loop() {
  if (digitalRead(pushbutton) == LOW) // Se o botão for pressionado
  {
     
     estadoled = !estadoled; // troca o estado do LED
     Serial.println("aaa");
    ReiniciaJogo();
    ProximoModo();
    while (digitalRead(pushbutton) == LOW);
    delay(100);
  }

  unsigned long currentMillis = millis();
  

  FastLED.show();
 
  if (currentMillis - previousMillisRaquete>= delayRaquete) {
    previousMillisRaquete = currentMillis;

    computaRaqueteSoma1();
    if(doisJogadores){
      computaRaqueteSoma2();
    }
  }
  
  if (currentMillis - previousMillisBolinha >= delayBolinha) {
    previousMillisBolinha = currentMillis;

  
    leds[matriz[bolinhaX][bolinhaY]] = CRGB::Black;
    bolinha();
    leds[matriz[bolinhaX][bolinhaY]] = CRGB::DarkRed;

  }

  
 
  
  


}
