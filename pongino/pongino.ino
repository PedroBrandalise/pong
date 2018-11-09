//display libs:
 
 #include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
 #include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
/*****************************************************************/

int TAMMX;
int TAMMY;
#define ESQUERDA -1
#define DIREITA 1
#define CIMA 1
#define BAIXO -1



//definir os pinos
#define pinoBotao1 D8
#define pinoBotao2 D7
#define SDA_PIN       D3 //d1
#define SCL_PIN       D5 //d2
#define ENDERECO_OLED 0x3C


//display
SSD1306Wire display(ENDERECO_OLED, SDA_PIN, SCL_PIN); // SDA, SCL -> Configuracao do display SSD1306

//SSD1306Wire  display(0x3c, D3, D5);
#define BOLA_TAM 1
#define R_TAM 8
#define R_ALTURA 2

void inicializacao();
void recebeComandos();
void logica();
void escreveTela();
void desenhaTela();
void ricocheteX();
void ricocheteY();
void teto();
void gameOver();

//char matrix[TAMMX][TAMMY];

int dirx = ESQUERDA;
int diry = CIMA;
int posicaoX;
int posicaoY;
int posicaoRaqueteX;
int posicaoRaqueteY;
int incX;
int incY;


void setup() {
  
  TAMMX = display.getWidth(); 
  TAMMY = display.getHeight();
  posicaoX= TAMMX-3, posicaoY= TAMMY/2;
  posicaoRaqueteX= R_TAM, posicaoRaqueteY = 0;

  incX = 1;
  incY = 1;
  
  //inicializacao();
  Serial.begin(57600);
  
  pinMode(pinoBotao1, INPUT );
  pinMode(pinoBotao2, INPUT );

  //display config
  display.init();

  // display.flipScreenVertically();

  display.setContrast(255);

}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(50);
  recebeComandos();
  logica();
  //escreveTela();
  desenhaTela();
  delay(20);
}


void recebeComandos(){
   char controle= getchar();
   
   if(digitalRead(pinoBotao1)== HIGH ) {
    if(posicaoRaqueteX == TAMMX-2){
      
    }else{
      posicaoRaqueteX++;
    }
    
    Serial.println(">");
    }
   if(digitalRead(pinoBotao2)== HIGH ) {
      Serial.println("<");
      //Serial.println(posicaoRaqueteX);
      if(posicaoRaqueteX == 1){
        
      }else{
        posicaoRaqueteX--;
      }
   }
}

/*int dirx = ESQUERDA;
int diry = CIMA;
int posicaoX;
int posicaoY;
int posicaoRaqueteX;
int posicaoRaqueteY;*/

void logica(){
  if(posicaoY == 0){
    gameOver();
  }

  
  if(posicaoY-BOLA_TAM == posicaoRaqueteY + R_ALTURA ){
    
    if(posicaoRaqueteX + R_TAM >= posicaoX && posicaoRaqueteX - R_TAM <= posicaoX){
      Serial.println("pong");
        ricocheteY();

    }
    
    
  }

  if(posicaoX - BOLA_TAM  == 1 || posicaoX + BOLA_TAM == TAMMX ){
    ricocheteX();
  }
  /*
  if (dirx==ESQUERDA){
    
    if (posicaoX==1)
    {
      dirx=DIREITA;
    }else{
      posicaoX--;
    }

  }else{
    if (posicaoX==TAMMX-2)
    {
      dirx=ESQUERDA;
    }else{
      posicaoX++;
    }
    
  }

  if (diry==CIMA )
  {
    if (posicaoY == 1)
    {
      diry = BAIXO;
    }else{
      posicaoY --;
    }

  }else{
    if (posicaoY == TAMMY - 2)
    {
      diry=CIMA;
    }else{
      posicaoY++;
    }
  }
  */
  if(posicaoY == TAMMY){
    teto();
  }

  posicaoX += incX;
  posicaoY += incY;
}

  /*if (dirx==DIREITA){
    dirx=ESQUERDA;
  }else{
    dirx=DIREITA;
  }
  if (diry==CIMA){
    dirx=BAIXO;
  }else{
    dirx=CIMA;
  }
  */

void ricocheteX(){
  incX *= -1; 
}

void ricocheteY(){
  incY *= -1;
}

void teto(){
  incY *= -1;
}

void gameOver(){
  
  posicaoY = TAMMY - 2;
  display.clear();
  display.flipScreenVertically();
  display.drawString(0, 26, "game over");
  display.display();

  delay(2000);
  display.flipScreenVertically();
}

void desenhaTela(){
  display.clear();
  //desenha a bolinha
  display.drawCircle(posicaoX, posicaoY, BOLA_TAM);
  //desenha duas requeti
  display.drawRect(posicaoRaqueteX -R_TAM, posicaoRaqueteY, 2 * R_TAM, R_ALTURA);
    
  //display.drawRect(0, 0, 16, 2);
  display.display();
}





