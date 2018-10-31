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

//display
SSD1306Wire  display(0x3c, D3, D5);
#define BOLA_TAM 1
#define R_TAM 8

void inicializacao();
void recebeComandos();
void logica();
void escreveTela();
void desenhaTela();

//char matrix[TAMMX][TAMMY];

int dirx = ESQUERDA;
int diry = CIMA;
int posicaoX;
int posicaoY;
int posicaoRaqueteX;
int posicaoRaqueteY;


void setup() {
  TAMMX = display.getWidth(); 
  TAMMY = display.getHeight();
  posicaoX= TAMMX-3, posicaoY= TAMMY/2;
  posicaoRaqueteX= R_TAM, posicaoRaqueteY = 0;
  
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
/*
void inicializacao(){
  for (int i = 0; i < TAMMX; ++i)
   {
    for (int j = 0; j < TAMMY; ++j)
    {
      if(i==0 || i == TAMMX-1 || j==0 || j ==TAMMY-1 ){
        matrix[i][j]='#';
      }
      else{
        matrix[i][j] = '.';
      }
    }
   } 
   //matrix[posicaoX][posicaoY]= 'o';
}
*/

void recebeComandos(){
   char controle= getchar();
   
   if(digitalRead(pinoBotao1)== HIGH ) {
    if(posicaoRaqueteX <= TAMMX-2){
      
    }else{
      posicaoRaqueteX+=2;
    }
    
    Serial.println(">");
    }
   if(digitalRead(pinoBotao2)== HIGH ) {
    if(posicaoRaqueteX >= 1){
      
    }else{
      posicaoRaqueteX-=2;
    }
    Serial.println("<");
   }
}

void logica(){
   // cout << posicaoX;
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

}

/*
void escreveTela(){
  
  for (int i = 0; i < TAMMX; ++i)
   {
    for (int j = 0; j < TAMMY; ++j)
    {
      if(i==posicaoX && j == posicaoY){
        Serial.print('o');
      }
      else if (i==posicaoRaqueteX && j == posicaoRaqueteY  )
      {
        Serial.print('~');
      }

      else{
        Serial.print(matrix[i][j]) ;
      }
    }
    //cout << endl;           
    Serial.print("\n\r");
   } 
   for(int i=0; i<20; i++){
    Serial.println('.');
   }
   Serial.write(12);
   Serial.write(13);
   Serial.write("\033c");
   
    


   //system("clear");

  

}
*/

void desenhaTela(){
  display.clear();
  //desenha a bolinha
  display.drawCircle(posicaoX, posicaoY, BOLA_TAM);
  //desenha duas requeti
  display.drawRect(posicaoRaqueteX -R_TAM, posicaoRaqueteY, 2 * R_TAM, 2);
    
  //display.drawRect(0, 0, 16, 2);
  display.display();
}



