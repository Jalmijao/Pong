#include <HCSR04.h>
#include <FastLED.h>

#define NUM_LEDS 64

#define DATA_PIN 8
#define CLOCK_PIN 13

UltraSonicDistanceSensor distanceSensor(10, 9);  // Initialize sensor that uses digital pins 13 and 12.
int ledAcender=0;
int matriz[8][8];
int posicaoY=3;
int posicaoX=3;
int adicaoY=0;
int adicaoX=1;
int posicaoRaquete=3;
int distanciaAnterior=0;
int contadorAndar=0;
int delayInicial=250;
int pontos=0;
int um=0;
int dois=0;
int zero=0;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  defineMatriz();
    Serial.begin(9600);
     FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  leds[matriz[0][posicaoRaquete]] = CRGB::Blue;
  leds[matriz[0][posicaoRaquete-1]] = CRGB::Blue;

   
}
void defineMatriz(){
  int i=0;
  int j=0;
  while(i<8){
    matriz[0][j]=i;
    i++;
    j++;

  }
  j=7;
  while(i<16){
    matriz[1][j]=i;
    i++;
    j--;
  }

  j=0;
  while(i<24){
    matriz[2][j]=i;
    i++;
    j++;
  }
  j=7;
  while(i<32){
    matriz[3][j]=i;
    i++;
    j--;
  }
  j=0;
  while(i<40){
    matriz[4][j]=i;
    i++;
    j++;
  }
  j=7;
  while(i<48){
    matriz[5][j]=i;
    i++;
    j--;
  }
  j=0;
  while(i<56){
    matriz[6][j]=i;
    i++;
    j++;
  }
  j=7;
  while(i<64){
    matriz[7][j]=i;
    i++;
    j--;
  }
}

void bolinha(){


  posicaoX=posicaoX+adicaoX;

  posicaoY=posicaoY+adicaoY;

  //Serial.println(posicaoX);
  //Serial.println(posicaoY);
  //Serial.println(adicaoY);
  // Serial.println(adicaoX);

  leds[matriz[posicaoX][posicaoY]] = CRGB::Blue;

 

  FastLED.show();
  leds[matriz[posicaoX][posicaoY]] = CRGB::Black;

  if(posicaoX == 1 && (posicaoY ==posicaoRaquete || posicaoY == posicaoRaquete-1)){
    //Serial.println("COLISAO");
    adicaoX=1;
    if(delayInicial>200){
      delayInicial=delayInicial-10;
    }

  }
  else if(posicaoX == 1 && adicaoY==-1 && posicaoY ==posicaoRaquete+1){
     //Serial.println("COLISAO");
     adicaoX=1;
     if(delayInicial>200){
       delayInicial=delayInicial-10;
     }
  } 
  else if(posicaoX == 1 && adicaoY==1 && posicaoY ==posicaoRaquete-2){
     //Serial.println("COLISAO");
     adicaoX=1;
     if(delayInicial>100){
       delayInicial=delayInicial-10;
     }
  } 
  else if(posicaoX == 0){
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

    posicaoX=3;
    posicaoY=3;
    adicaoY=0;
    adicaoX=1;
    pontos=pontos+1;
    Serial.println("Quantidade de pontos = ");
    Serial.println(pontos);

  for(int i=0;i<pontos;i++){
      leds[matriz[6][i]] = CRGB::DarkRed;
    }
    FastLED.show();
    delay(500);
    for(int i=0;i<pontos;i++){
      leds[matriz[6][i]] = CRGB::Black;
    }
    FastLED.show();

    if(pontos==8){
      delayInicial=300;

      pontos=0;
      for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
          leds[matriz[i][j]] = CRGB::DarkRed;
        }
      }
      FastLED.show();
      delay(2000);
      for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
          leds[matriz[i][j]] = CRGB::Black;
        }
      }
      FastLED.show();

    }
    
    
 


  }



  if(posicaoX == 7){
      int randomico=random(0,3);
   
      if(adicaoY == 0){
        adicaoY=1;
      }
      if(randomico==1){
        adicaoY=-1;

      }
      else if(randomico==2){
        adicaoY=0;
        
      }
      
      adicaoX=adicaoX*-1;

  }


  else if(posicaoY == 7 || posicaoY == 0){
      if(adicaoY == 0){
        adicaoY=1;
      }
      adicaoY=adicaoY*-1;
  }
 

}
void computaRaqueteSoma(){
    float distancia = distanceSensor.measureDistanceCm(); 
    //Serial.println(posicaoRaquete);
    //Serial.println(distancia);

    if(distancia<20 ){
      if(distancia > 10 && posicaoRaquete <7){

        distanciaAnterior=distancia;
        leds[matriz[0][posicaoRaquete]] = CRGB::Black;
        leds[matriz[0][posicaoRaquete-1]] = CRGB::Black;

        posicaoRaquete=posicaoRaquete+1;

        leds[matriz[0][posicaoRaquete]] = CRGB::Blue;
        leds[matriz[0][posicaoRaquete-1]] = CRGB::Blue;
      }
      else if(distancia < 7 && posicaoRaquete >1){

        leds[matriz[0][posicaoRaquete]] = CRGB::Black;
        leds[matriz[0][posicaoRaquete-1]] = CRGB::Black;

        posicaoRaquete=posicaoRaquete-1;
        distanciaAnterior=distancia;

        leds[matriz[0][posicaoRaquete]] = CRGB::Blue;
        leds[matriz[0][posicaoRaquete-1]] = CRGB::Blue;

      }

    }
}

void loop() { 

  delay(delayInicial);

  //ComputaRaquetePosicao();
   computaRaqueteSoma();
   bolinha();




}