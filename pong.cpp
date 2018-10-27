#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
//tamanhos da matriz, em x e y
#define TAMMX 20
#define TAMMY 33
#define ESQUERDA -1
#define DIREITA 1
#define CIMA 1
#define BAIXO -1


using namespace std;

void inicializacao();
void recebeComandos();
void logica();
void escreveTela();

char matrix[TAMMX][TAMMY];
int posicaoX= TAMMX-3, posicaoY= TAMMY/2;
int posicaoRaqueteX= TAMMX-2, posicaoRaqueteY = TAMMY/2;
int dirx = ESQUERDA;
int diry = CIMA;


int main(){

	inicializacao();
	while(1){
		usleep(50*1000);
		//recebeComandos();
		logica();
		escreveTela();
	}
	return 0;
}

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

void recebeComandos(){
	 char controle= getchar();
	 // if(cin >> controle){

	 // if (controle == 'a'){
	 // 	posicaoRaqueteY--;
	 // }else if (controle == 'd')
	 // {
	 // 	posicaoRaqueteY++;
	 // }
	 // }
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

void escreveTela(){
	
	for (int i = 0; i < TAMMX; ++i)
	 {
	 	for (int j = 0; j < TAMMY; ++j)
	 	{
	 		if(i==posicaoX && j == posicaoY){
	 			cout << 'o';
	 		}
	 		else if (i==posicaoRaqueteX && j == posicaoRaqueteY  )
	 		{
	 			cout << '~';
	 		}

	 		else{
	 			cout << matrix[i][j] ;
	 		}
	 	}
	 	cout << endl;						
	 } 

	 system("clear");



}




