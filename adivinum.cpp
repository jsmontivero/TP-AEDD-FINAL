#include <iostream>
#include "headers/adivinum.h"

using namespace std;

int adivinum() {

	
	// v1 ------> vector con el numero secreto.   //
	// v2 ------> vector con el numero ingresado. //
	
	int num_sec = numeroSecreto(), intento=1, X, vidas, iguales=0, diferentes=0;     //variables
	int v1[__MAX_TAM], v2[__MAX_TAM];                        	 //vectore
	bool triunfo=false;
	
	cargarVector(num_sec,v1);

	
	/*-----------------intentos-------------*/
	do{
		vidas = 11 - intento;
		interfaz_adivinum(intento, vidas, iguales, diferentes, X);
		cin >> X;
		
		while(!cuatroCifras(X))
		{      
			cout << "\n\n                 El numero debe tener " << __MAX_TAM << " cifras. Vuelva a intentarlo." << endl;
			Sleep(1500);
			system("cls");
			interfaz_adivinum(intento, vidas, 0, 0, 0000);
			cin >> X;
		}
		
		cargarVector(X,v2);
		comparar (v1, v2,iguales, diferentes);
		
		if(X==num_sec)
			triunfo=true;
		
		if(!triunfo)
			intento++;
		system("cls");
	} while(!triunfo and intento<=10);
	/*-------------------------------------*/
	
	if(triunfo)
		interfaz_adivinum(intento, -2, 0, 0, 0000);
	else
		interfaz_adivinum(intento, -1, 0, 0, 0000);
	
	system("pause");
	return 11-intento;
}

bool chequearNumero(int N){
	
	int v1[__MAX_TAM];
	bool verdad=false;
	
	
	cargarVector(N, v1);
	
	
	if(v1[0]==v1[1] or v1[0]==v1[2] or v1[0]==v1[3])
		verdad=true;
	else if(v1[1]==v1[2] or v1[1]==v1[3])
		verdad=true;
	else if(v1[2]==v1[3])
		verdad=true;
	
	
	return verdad;
}
int numeroSecreto(){
	
	int N;
	srand(time(NULL));
	do{
		// inicio + rand() % (fin+1 - inicio);
		N = 1000 + rand()% (10000-1000);
	} while(chequearNumero(N));
	
	return N;
	
}
bool cuatroCifras(int N){
	
	bool verdad=true;
	
	if(N<1000 or N>9999)
		verdad=false;
	
	return verdad;
}
void cargarVector(int N, int v[]){
	
	for(int i=3; i>=0; i--)
	{
		v[i] = (N%10);
		N /= 10;
	}
	
}


void comparar(int secreto [],int ingresado[], int& iguales, int& diferentes){
	iguales=0;
	diferentes=0;
	
	for (int j=0; j<4; j++)
	{
		for (int i=0; i<4; i++)
		{
			if (secreto[j]==ingresado[i])
			{
				if(j==i)
					iguales++;
				else
					diferentes++;
			}
		}
		
	} 
	
}

void interfaz_adivinum(int x, int y, int iguales, int diferentes, int numero){
	switch(y){
	case 10:
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |" << endl
			<< "           #";
		for(int i=0; i<28; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		cout << "#     |" << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
		
	case 9:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<24; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<4; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;	
	case 8:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<21; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<7; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
	case 7:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<18; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<10; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
		
	case 6:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<15; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<13; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
	case 5:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<12; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<16; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
	case 4:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<9; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<19; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
	case 3:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<6; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<22; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
	case 2:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<3; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<25; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
	case 1:
		
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |            -" << numero << "-" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |    Cant. Misma Posicion: " << iguales << endl
			<< "           #";
		for(int i=0; i<1; i++) cout << (char)178;
		cout << (char)177 << (char)176;
		for(int l=0; l<27; l++) cout << " ";
		cout << "#     |  Cant. Distinta Posicion: " << diferentes << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |       Intento " << x << ": ";
		break;
	case -1:
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |" << endl
			<< "           #            Perdiste          #     |" << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl;
		break;
	case -2:
		cout << setw(47) << "=====Adivinum=====" << endl << endl << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                     Vida Restante              |" << endl
			<< "           ################################     |" << endl
			<< "           #           Ganaste!!!         #     |" << endl
			<< "           ################################     |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl
			<< "                                                |" << endl;
		break;
	}
}
