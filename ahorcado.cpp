#include <iostream>
#include "headers/ahorcado.h"
using namespace std;
const int TT=4;
const int TF=20;
int ahorcado() {

	// tam_palabra ------> cant de letras. //
	// palabra ---------> palabra ya seleccionada. //
	// guiones ---------> palabra guiones. // 
	
	char letra_ingreso, palabra[TF], PalabrasTotal[30][TF]= {
		"COMPILADOR",
			"ENTORNO",
			"COMPUTADORA",
			"ESTRUCTURA",
			"SELECCION",
			"REPETICION",
			"DIRECTIVA",
			"ALGORITMO",
			"PROGRAMA",
			"EJECUCION",
			"INT",
			"FLOAT",
			"CHAR",
			"DOUBLE",
			"LONG",
			"IF",
			"ELSE",
			"FOR",
			"WHILE",
			"RETURN",
			"BREAK",
			"SWITCH",
			"CASE",
			"MAIN",
			"INCLUDE",
			"DEFINE",
			"STRUCT",
			"CIN",
			"COUT",
			"ENDL"
	}, partes[10][17] = {
		"CABEZA", 
			"TRONCO", 
			"BRAZO IZQUIERDO", 
			"BRAZO DERECHO", 
			"PIERNA DERECHA", 
			"PIERNA IZQUIERDA", 
			"MANO DERECHA", 
			"MANO IZQUIERDA", 
			"PIE IZQUIERDO", 
			"PIE DERECHO"
	};
	
	
	char ingresadas[2][26] = { 0 }, guiones[TF];
	int aleatorio, tam_palabra, aciertos=0, tam_hombrecito=0,cont_ingresada = 0;
	
	srand(time(NULL));
	aleatorio = rand()%30;
	
	cargarVector(palabra, PalabrasTotal[aleatorio]);
	tam_palabra = cantLetras(PalabrasTotal[aleatorio]);
	cargarGuiones(guiones, tam_palabra);
	
	do{
		/// Presentacion -- Imrpimimos el registro de Guiones y Hombrecito ///
		imprimirLog(guiones, partes, ingresadas, palabra, tam_palabra, tam_hombrecito);
		cin >> letra_ingreso;
		
		bool esN = esNumero(letra_ingreso);
		bool seRep = seRepite(letra_ingreso, ingresadas, cont_ingresada);
		while(esN || seRep) {
			
			if(esN)
				cout << "\n\n                    ERROR - Solo puedes ingresar letras!\n" << endl;
			else if(seRep)
				cout << "\n\n                 ERROR - No se puede ingresar una letra ya usada!\n" << endl;
			
			system("pause");
			
			/// Si ingreso mal envia un mensaje y luego de que presione una tecla vuelve a poner la presentacion y a leer de nuevo ///
			imprimirLog(guiones, partes, ingresadas, palabra, tam_palabra, tam_hombrecito);
			cin >> letra_ingreso;
			
			esN = esNumero(letra_ingreso);
			seRep = seRepite(letra_ingreso,ingresadas, cont_ingresada);
		}
		
		/*----------------ingreso erroneo-------------*/
		if (letra_ingreso>=97 and letra_ingreso<=122)
			letra_ingreso-=32;
		/*---------------------------------------*/
		
		
		
		if(!verificacion(letra_ingreso, palabra, tam_palabra, aciertos, guiones)) 
		{
			/// Registro columna 0 es para erroneas y columna 1 es para acertadas ///
			ingresadas[0][tam_hombrecito]=letra_ingreso;		
			tam_hombrecito++;
		}
		/*------------------------------------------------------------*/
		else
		{
			/// Registro columna 0 es para erroneas y columna 1 es para acertadas ///
			ingresadas[1][cont_ingresada]=letra_ingreso;
			cont_ingresada++;
		}
		
	} while(aciertos!=tam_palabra and tam_hombrecito<10);
	
	imprimirLog(guiones, partes, ingresadas, palabra, tam_palabra, tam_hombrecito);
	if(tam_hombrecito >= 10) {
		tam_hombrecito = 25;
		cout << "\n\n                    Lastimosamente perdiste, vuelve pronto!" << endl;
	}
	else
		cout << "\n\n                    GANASTE! - Tu puntaje fue de " << 50-(2*tam_hombrecito) << " puntos." << endl;
	
	system("pause");
	return 50-(2*tam_hombrecito);
}

int cantLetras(char v[TF]){
	int i=0;
	
	do{
		i++;
	} while(v[i]>='A' and v[i]<='Z' );
	return i;
}

void cargarGuiones(char v[TF], int tam){
	int i;
	for(i=0; i<tam; i++)
		v[i] = '-';
	
	v[i] = '\0';
}

void cargarVector(char palabra[TF], char v[TF]){
	
	int i, TL = cantLetras(v);
	for(i=0; i<TL; i++)
		palabra[i] = v[i];
	
	palabra[i] = '\0';
}

void printGuiones(char guiones[TF], int tam_palabra) {
	for(int i=0; i<tam_palabra; i++)
		cout << " " << guiones[i];
}
void imprimirLog(char guiones[TF], char partes[10][17], char ingresadas[2][26], char palabra[], int tam_palabra, int tam_hombrecito) {
	system("cls");
	cout << "                      ============ AHORCADO ============\n\n";
	
	switch(tam_hombrecito) {
	case 0:
		
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |     "; /*<< printGuiones(guiones, tam_palabra) << endl;*/
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		
		break;
	case 1:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |                              |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |                                           |     "; /*<< printGuiones(guiones, tam_palabra) << endl;*/
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		break;
	case 2:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----                               |" << endl;	
		cout <<  "   | |         |                                 |     "; /*<< printGuiones(guiones, tam_palabra) << endl;*/
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |         |                                 |" << endl;
		cout <<  "   | |         |                                 |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |"<< endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		break;
	case 3:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----         " << ingresadas[0][2] << " - " << " BRAZO IZQUIERDO  |" << endl;	
		cout <<  "   | |         |                                 |     ";
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |         |                                 |" << endl;
		cout <<  "   | |         |" << char(92) << "                                |" << endl;
		cout <<  "   | |         | " << char(92) << "                               |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |"<< endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		break;
	case 4:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----         " << ingresadas[0][2] << " - " << " BRAZO IZQUIERDO  |" << endl;	
		cout <<  "   | |         |           " << ingresadas[0][3] << " - " << " BRAZO DERECHO    |     ";
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |         |                                 |" << endl;
		cout <<  "   | |        /|" << char(92) << "                                |" << endl;
		cout <<  "   | |       / | " << char(92) << "                               |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |"<< endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		break;
	case 5:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----         " << ingresadas[0][2] << " - " << " BRAZO IZQUIERDO  |" << endl;	
		cout <<  "   | |         |           " << ingresadas[0][3] << " - " << " BRAZO DERECHO    |     ";
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |         |           " << ingresadas[0][4] << " - " << " PIERNA IZQUIERDA |" << endl;
		cout <<  "   | |        /|" << char(92) << "                                |" << endl;
		cout <<  "   | |       / | " << char(92) << "                               |" << endl;
		cout <<  "   | |          "<< char(92) << "                                |" << endl;
		cout <<  "   | |           "  << char(92) << "                               |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		
		break;
	case 6:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----         " << ingresadas[0][2] << " - " << " BRAZO IZQUIERDO  |" << endl;	
		cout <<  "   | |         |           " << ingresadas[0][3] << " - " << " BRAZO DERECHO    |     ";
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |         |           " << ingresadas[0][4] << " - " << " PIERNA IZQUIERDA |" << endl;
		cout <<  "   | |        /|" << char(92) << "          " << ingresadas[0][5] << " - " << " PIERNA DERECHA   |" << endl;
		cout <<  "   | |       / | " << char(92) << "                               |" << endl;
		cout <<  "   | |        / "<< char(92) << "                                |" << endl;
		cout <<  "   | |       /   "  << char(92) << "                               |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		break;
	case 7:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----         " << ingresadas[0][2] << " - " << " BRAZO IZQUIERDO  |" << endl;	
		cout <<  "   | |         |           " << ingresadas[0][3] << " - " << " BRAZO DERECHO    |     ";
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |         |           " << ingresadas[0][4] << " - " << " PIERNA IZQUIERDA |" << endl;
		cout <<  "   | |        /|" << char(92) << "          " << ingresadas[0][5] << " - " << " PIERNA DERECHA   |" << endl;
		cout <<  "   | |       / | " << char(92) << "         " << ingresadas[0][6] << " - " << " MANO IZQUIERDA   |" << endl;
		cout <<  "   | |         |  " << char(79) << "                              |" << endl;
		cout <<  "   | |        / "<< char(92) << "                                |" << endl;
		cout <<  "   | |       /   "  << char(92) << "                               |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		break;
	case 8:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----         " << ingresadas[0][2] << " - " << " BRAZO IZQUIERDO  |" << endl;	
		cout <<  "   | |         |           " << ingresadas[0][3] << " - " << " BRAZO DERECHO    |     ";
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |         |           " << ingresadas[0][4] << " - " << " PIERNA IZQUIERDA |" << endl;
		cout <<  "   | |        /|" << char(92) << "          " << ingresadas[0][5] << " - " << " PIERNA DERECHA   |" << endl;
		cout <<  "   | |       / | " << char(92) << "         " << ingresadas[0][6] << " - " << " MANO IZQUIERDA   |" << endl;
		cout <<  "   | |      " << char(79) << "  |  " << char(79) << "        " << ingresadas[0][7] << " - " << " MANO DERECHA     |" << endl;
		cout <<  "   | |        / "<< char(92) << "                                |" << endl;
		cout <<  "   | |       /   "  << char(92) << "                               |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		break;
	case 9:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | O O |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----         " << ingresadas[0][2] << " - " << " BRAZO IZQUIERDO  |" << endl;	
		cout <<  "   | |         |           " << ingresadas[0][3] << " - " << " BRAZO DERECHO    |     ";
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |         |           " << ingresadas[0][4] << " - " << " PIERNA IZQUIERDA |" << endl;
		cout <<  "   | |        /|" << char(92) << "          " << ingresadas[0][5] << " - " << " PIERNA DERECHA   |" << endl;
		cout <<  "   | |       / | " << char(92) << "         " << ingresadas[0][6] << " - " << " MANO IZQUIERDA   |" << endl;
		cout <<  "   | |      " << char(79) << "  |  " << char(79) << "        " << ingresadas[0][7] << " - " << " MANO DERECHA     |" << endl;
		cout <<  "   | |        / "<< char(92) << "          " << ingresadas[0][7] << " - " << " PIE IZQUIERDO    |" << endl;
		cout <<  "   | |       /   "  << char(92) << "                               |" << endl;
		cout <<  "   | |            "  << char(79) << "                              |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |       Ingrese una Letra: ";
		
		break;
	case 10:
		cout <<  "    ___________________________                  " << endl;
		cout <<  "   |  ________))_______________|                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |        ||                                 |" << endl;
		cout <<  "   | |       -----                               |" << endl;
		cout <<  "   | |      | X X |        " << ingresadas[0][0] << " - " << " CABEZA           |" << endl;
		cout <<  "   | |      |     |        " << ingresadas[0][1] << " - " << " TRONCO           |" << endl;
		cout <<  "   | |       -----         " << ingresadas[0][2] << " - " << " BRAZO IZQUIERDO  |" << endl;	
		cout <<  "   | |         |           " << ingresadas[0][3] << " - " << " BRAZO DERECHO    |     ";
		
		/// Imprime los guiones a la derecha y hace el salto de linea para que no se interpongan ///
		printGuiones(guiones, tam_palabra);
		cout << endl;
		
		cout <<  "   | |        (|)          " << ingresadas[0][4] << " - " << " PIERNA IZQUIERDA |" << endl;
		cout <<  "   | |        /|" << char(92) << "          " << ingresadas[0][5] << " - " << " PIERNA DERECHA   |" << endl;
		cout <<  "   | |       / | " << char(92) << "         " << ingresadas[0][6] << " - " << " MANO IZQUIERDA   |" << endl;
		cout <<  "   | |      " << char(79) << "  |  " << char(79) << "        " << ingresadas[0][7] << " - " << " MANO DERECHA     |" << endl;
		
		cout <<  "   | |        / "<< char(92) << "          " << ingresadas[0][8] << " - " << " PIE IZQUIERDO    |" << endl;
		cout <<  "   | |       /   "  << char(92) << "         " << ingresadas[0][9] << " - " << " PIE DERECHO      |     ";
		
		/// Imprime la palabra a adivinar porque ya perdio ///
		printGuiones(palabra, tam_palabra);
		cout << endl;
		
		cout <<  "   | |      " << char(79) << "     "  << char(79) << "                              |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   | |                                           |" << endl;
		cout <<  "   |--------------------------------             |";
		break;
	}
}

bool esNumero(int x){
	if((x>=97 and x<=122) or (x>=65 and x<=90))
		return false;
	else
		return true;
}

bool seRepite (char x,char y[2][26], int cont_ingresadas){
	bool verdad = false;
	int i=0;
	while (!verdad and i<26){
		if (x==y[0][i] || x-32 == y[0][i])
			verdad=true;
		else if(x==y[1][i] || x-32 == y[1][i])
			verdad=true;
		
		i++;
		
	}
	return verdad;
}

bool verificacion(char letra_ingreso, char palabra[TF], int tam_palabra, int& aciertos, char guiones[17]){
	
	bool encontrado=false;
	
	for(int i=0; i<tam_palabra; i++){
		if(letra_ingreso==palabra[i])
		{
			guiones[i] = letra_ingreso;
			aciertos++;
			encontrado=true;
		}
	}
	
	return encontrado;
}
