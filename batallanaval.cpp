#include <iostream>
#include "headers/batallanaval.h"

using namespace std;

int batallaNaval() {

	char tablero [10][10],modificado [10][10], coordenada_y;
	int coordenada_x, puntos=100, barcosrestantes=23, barcosHundidos=0;
	cargarTablero(tablero);
	cargarModificado(modificado);
	
	do{
		imprimirPresentacion(modificado, puntos, barcosHundidos);
		cin >> coordenada_y >> coordenada_x;
		
		coordenada_y = toupper(coordenada_y);
		coordenada_y-=65;
		coordenada_x-=1;
		
		while(modificado[int(coordenada_y)][coordenada_x] != '?' || posicionInvalida(coordenada_y, coordenada_x)) {
			if(!posicionInvalida(coordenada_y, coordenada_x))
				cout << "\n\n                ERROR - No puedes disparar en una posicion ya disparada!" << endl;
			else
				cout << "\n\n                      ERROR - La posicion ingresada es invalida!" << endl;
			
			Sleep(1500);
			system("cls");
			
			imprimirPresentacion(modificado, puntos, barcosHundidos);
			cin >> coordenada_y >> coordenada_x ; 
			
			coordenada_y = toupper(coordenada_y);
			coordenada_y-=65;
			coordenada_x-=1;
		}
		
		compararTablero(tablero, modificado,coordenada_y,coordenada_x, puntos, barcosrestantes, barcosHundidos);
		Sleep(1500);
		system("cls");
	}while(puntos>0 and barcosrestantes>0);
	
	system("pause");
	return puntos;
}
void cargarTablero(char tablero[10][10]){
	srand(time(NULL));
	
	int barcos[7]={5,4,4,3,3,2,2};
	char barco='a';
	int x,y,longitud,l,r;
	bool listo,horizontal;
	
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++)
			tablero[i][j]='.';
	}
	
	for(int i=0;i<7;i++)
	{
		listo=false;
		do
		{
			longitud=barcos[i];
			x=rand()%10;
			y=rand()%10;
			horizontal=rand()%2;
			l=r=(horizontal)?x:y;
			if(tablero[x][y]=='.')
			{
				longitud--;
				for(int j=((horizontal)?x:y)+1;j<10 && !listo && tablero[x+horizontal*(j-x)][y+(!horizontal)*(j-y)]=='.';j++)
				{
					longitud--;
					r=j;
					if(longitud==0) listo=true;
				}
				for(int j=((horizontal)?x:y)-1;j>=0 && !listo && tablero[x+horizontal*(j-x)][y+(!horizontal)*(j-y)]=='.';j--)
				{
					longitud--;
					l=j;
					if(longitud==0) listo=true;
				}
			}
		}
		while(!listo);
		for(int j=l;j<=r;j++) tablero[x+horizontal*(j-x)][y+(!horizontal)*(j-y)]=barco;
		barco++;
	}
	for(int i=0;i<10;i++)
	{
		do
		{
			x=rand()%10;
			y=rand()%10;
		}while(tablero[x][y]!='.');
		tablero[x][y]='m';
	}
	return;
}
void cargarModificado(char modificado [][10]){
	for (int i=0 ; i<10 ; i++){
		for (int j=0 ; j<10 ;j++){
			modificado [i][j]= '?';
		}
	}
}
void imprimirPresentacion(char modificado[][10], int puntaje, int hundidos) {
	cout << setw(51) << "======Batalla Naval=====";
	cout << "\n\n\n\n";
	
	cout << setw(6);
	for(int i = 1; i <= 10; i++) {
		if(i < 10)
			cout << i << " ";
		else
			cout << i << setw(25) << "|\n" << setw(50) << "|\n";
	}
	
	for(int i = 0; i < 10; i++) {
		cout << setw(3);
		cout << char(65+i);
		cout << setw(3); 
		
		for(int j = 0; j < 10; j++) {
			if(j < 9)
				cout << modificado[i][j] << " ";
			else {
				cout << modificado[i][j] << "                        |    ";
				if(i == 0)
					cout << " Tu puntaje actual es de";
				else if(i == 2)
					cout << "      " << puntaje << " puntos";
				else if(i == 5)
					cout << " " << hundidos << " barco(s) hundido(s)";
				else if(i == 7)
					cout << 7-hundidos << " barco(s) restantes(s)";
				else if(i == 9)
					cout << "Ingrese una coordenada: ";
			}
		}
		if(i < 9)
			cout << endl;
	}
}
void mostrarMatriz(char modificado[][10]){
	for (int i=0 ; i<10 ; i++){
		for (int j=0 ; j<10 ;j++){
			cout << modificado [i][j] ;
		}
		cout << endl;
	}
}
void compararTablero(char tablero[][10],char modificado[][10],int y,int x, int& pts,int& barcos, int& barcosHundidos){
	if(tablero[y][x]=='.')
	{
		modificado[y][x] = 'a';
		pts--;
		cout << "\n\n                            AGUA! - Perdes 1 punto." << endl;  
	}
	else if(tablero[y][x]=='m')
	{
		modificado[y][x] = 'm';
		pts-=5;
		cout << "\n\n                            MINA! - Perdes 5 puntos." << endl;  
	}
	else {
		// Si no hay mas barquitos de la letra del barquito ira H
		
		// saber tamaño del barco y ver que no halla mas
		int tam = tamanioBarco(tablero[y][x]);
		
		if(hayBarco(tablero, y, x, tam)) {
			modificado[y][x] = 'F';
			cout << "\n\n                       FUEGO! - Le diste a un barco!" << endl;
		}
		else {
			modificado[y][x] = '#';
			modificarExplosion(tablero, modificado, y, x, tam);
			barcosHundidos++;
			cout << "\n\n                    FUEGO y HUNDIDO! - Hundiste el barco!" << endl;
		}
		barcos-=1;
	}
	
	tablero[y][x] = toupper(tablero[y][x]);
}

void modificarExplosion(char tablero[][10], char modificado[][10], int y, int x, int tam) {
	char barco = tablero[y][x];
	for(int i=1; i<=tam; i++) {
		if(tablero[y+i][x] == toupper(barco))
			modificado[y+i][x] = '#';
		else if(tablero[y][x+i] == toupper(barco))
			modificado[y][x+i] = '#';
			
	}
	
	for(int i = tam; i > 0; i--) {
		if(tablero[y-i][x] == toupper(barco))
			modificado[y-i][x] = '#';
		else if(tablero[y][x-i] == toupper(barco))
			modificado[y][x-i] = '#';	
	}
}
int tamanioBarco(char barquito){
	if(barquito == 'a')
		return 5;
	else if(barquito == 'b' || barquito == 'c')
		return 4;
	else if(barquito == 'd' || barquito == 'e')
		return 3;
	else if(barquito == 'f' || barquito == 'g')
		return 2;
	
	return -1;
}
bool hayBarco(char tablero[][10],int y, int x, int tam){
	char barco=tablero[y][x];
	int barquitos=0;
	
	for(int i=1; i<=tam; i++) {
		if(tablero[y+i][x] == barco)
			barquitos++;
		else if(tablero[y][x+i] == barco)
			barquitos++;
	}
	for(int i = tam; i > 0; i--) {
		if(tablero[y-i][x] == barco)
			barquitos++;
		else if(tablero[y][x-i] == barco)
			barquitos++;
		
	}
	if(barquitos>0)
		return 1;
	
	return 0;
}

bool posicionInvalida(int coordenada_y, int coordenada_x) {
	if((coordenada_y < 0 || coordenada_y > 9) || (coordenada_x < 0 || coordenada_x > 9)) // Si la coordenada_y no esta entre A y J o la coordenada_x no esta entre 1 y 10
		return true;
	
	return false;
}
