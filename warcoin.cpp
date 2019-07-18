#include <iostream>
#include "headers/warcoin.h"

using namespace std;


int warCoin() {

	
	int minima,maxima,cantinicial=0,usuario,npc=0;
	bool comienza;	
	
	interfaz_warCoin(-1, minima, maxima, cantinicial, 0);
	
	
	cantinicial = cant(minima);
	comienza = empieza();
	
	
	do{
		system("cls");
		
		if (comienza==1){
			interfaz_warCoin(-2, minima, maxima, cantinicial, npc);
			cin >> usuario;
			if (usuario<minima or usuario>maxima) {
				cout<<"           ERROR: se deben desapilar entre " << minima << " y " << maxima <<" monedas. Volvé a intentarlo!" << endl;
				Sleep(1500);
			}
			else{
				cantinicial-=usuario;
				comienza=0;
			}			
			
		} else if (comienza==0){
			interfaz_warCoin(-2, minima, maxima, cantinicial, 0);
			npc= pc( minima,maxima);
			cantinicial-=npc;
			
			comienza=1;
			Sleep(1500);
		}
		
		if(cantinicial < 0)
			cantinicial=0;
		
		//
	}
	while(cantinicial>minima);
	
	system("cls");
	if ( (comienza==1 && cantinicial != 0 ) || (comienza==0 && cantinicial == 0) )
	{
		interfaz_warCoin(-3, minima, maxima, 0, 0);
		cout <<"\n\n                       ¡Gano el usuario! Puntaje obtenido: 5 puntos" << endl;
	}
	else if ( (comienza==0 && cantinicial != 0) || (comienza==1 && cantinicial == 0) )
	{
		interfaz_warCoin(-3, minima, maxima, 0, -1);
		cout <<"\n\n                       ¡Gano la computadora! Puntaje obtenido: 0 puntos" << endl;
	}
	
	system("pause");
	
	if ( (comienza==1 && cantinicial != 0) || (comienza==0 && cantinicial == 0) )
		return 5;
	else if ( (comienza==0 && cantinicial != 0) || (comienza==1 && cantinicial == 0) )
		return 0;
}
int cant(int min){
	srand(time(NULL));
	int valor = min+rand()%(50-min);
	
	return valor;
}
bool empieza (){
	int valor;
	srand(time(NULL));
	valor = 1+rand()%(3-1);
	if (valor==1)
		return true;
	else
		return false;
}
int pc (int min, int max){
	srand(time(NULL));
	return min+rand()%((max)-(min));
}
void interfaz_warCoin(int caso, int& minima, int& maxima, int restantes, int npc){
	
	int contador=0;
	
	switch(caso)
	{
	case -1:
		cout << setw(47) << "=====WarCoin=====" << endl << endl << endl
			<< "	                              |" << endl	
			<< "                                      |" << endl
			<< "             Monedas                  |" << endl;
		
		for(int i=0; i<5; i++){
			cout << "       ";
			for(int j=0; j<10; j++){
				cout << "O ";
			}
			cout << "           |";
			if(i==2) {
				cout << "     Ingrese la cantidad minima de monedas a retirar : " ;
				cin >> minima;
				cin.ignore();
			}
			else if(i==4) {
				cout << "     Ingrese la cantidad maxima de monedas a retirar : ";
				cin >> maxima;
				cin.ignore();
			}
			else
					cout << endl;
		}
		
		cout << "                                      |" << endl
			<< "                                      |" << endl
			<< "                                      |" << endl;
		break;
		
	case -2:
		cout << setw(47) << "=====WarCoin=====" << endl << endl << endl
			<< "	                              |" << endl	
			<< "                                      |" << endl;
		if(restantes<10)
			cout << "        ";
		else
			cout << "       ";
		
		if(npc != 0)
			cout << "Monedas restantes : " << restantes << "         |       La computadora saco " << npc << " monedas." << endl;
		else
			cout << "Monedas restantes : " << restantes << "         |" << endl;
		/*---------------matrix---------------------*/
		for(int i=0; i<5; i++){
			cout << "       ";
			for(int j=0; j<10; j++){
				if(contador<restantes)
					cout << "O ";
				else
					cout << "  ";
				contador++;
			}
			/*--------------------------------------*/
			
			cout << "           |";
			if(i == 2)
				cout << "       Podes sacar entre " << minima << " y " << maxima << " monedas.";
			
			cout << endl;
		}
		
		cout << "                                      |" << endl
			<< "                                      |" << endl
			<< "                                      |       Ingrese la cantidad de monedas: ";
		
		break;
		
	case -3:
		cout << setw(47) << "=====WarCoin=====" << endl << endl << endl
			<< "	                              |" << endl	
			<< "                                      |" << endl;
		
		cout << "        Monedas restantes : " << 0 << "         |";
		if(npc == -1)
			cout << "             Perdiste!" << endl;
		else
			cout << "             Ganaste!" << endl;
		
		for(int i=0; i<5; i++){
			cout << "       ";
			for(int j=0; j<10; j++){
				cout << "  ";
			}
			cout << "           |";
			cout << endl;
		}
		
		cout << "                                      |" << endl
			<< "                                      |" << endl
			<< "                                      |" << endl;
		break;
		
	}
}
