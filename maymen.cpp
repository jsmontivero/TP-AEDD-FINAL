#include <iostream>
#include "headers/maymen.h"

using namespace std;


int mayMen() {

	
	int num_sec, x, mayor=999, menor=0, intento=1;
	bool verdad=false;
	
	srand(time(NULL));
	num_sec = menor + rand() % (mayor + 1 - menor);
	
	interfaz_mayMen(x, menor, mayor, intento-1, num_sec);
	
	do{
		cin >> x;
		while(x < 0 || x > 999) {
			cout << "\n\n                     ERROR - El numero debe estar entre 0 y 999" << endl;
			Sleep(1500);
			system("cls");
			
			interfaz_mayMen(x, menor, mayor, intento-1, num_sec);
			cin >> x;
		}
		system("cls");
		verdad = seAcerto(x, num_sec, intento);
		
		if(!verdad) {
			actualizar(x, menor, mayor, num_sec);
			interfaz_mayMen(x, menor, mayor, intento, num_sec);	
			intento++;
		}		
	} while(!verdad);
	
	system("cls");	
	if(num_sec == x) {
		interfaz_mayMen(x, menor, mayor, 12, num_sec);
		cout << "\n\n" << setw(50) << "Ganaste! Tu puntaje fue de " << 11-intento << " puntos." << endl;
	}
	else {
		interfaz_mayMen(x, menor, mayor, intento, num_sec);
		cout << "\n\n" << setw(58) << "Perdiste, mas suerte a la proxima!" << endl; 
	}
	
	system("pause");
	return 11-intento;
}

void interfaz_mayMen(int x, int men, int may, int y, int num_sec){
	y = 10-y;
	switch(y) {
		// A estos 2 primeros cases para mi le faltarian algo mas abajo del ganaste o perdiste
	case -2:
		cout << setw(47) << "=====MayMen=====" << endl             
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero podia estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##                    ##                |" << endl
			<<"        ##      GANASTE       ##                |" << endl//parte de arriba
			<<"        ##                    ##                |" << endl
			<<"        ##                    ##                |" << endl// parte media
			<<"        ##                    ##                |" << endl
			<<"        ##                    ##                |" << endl
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |" << endl;
		break;
	case 0:
		cout << setw(47) << "=====MayMen=====" << endl             
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero estaba entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##                    ##                |" << endl
			<<"        ##      PERDISTE      ##                |" << endl//parte de arriba
			<<"        ##                    ##                |      El numero era " << endl
			<<"        ##                    ##                |" << endl// parte media
			<<"        ##                    ##                |" << endl
			<<"        ##                    ##                |          [" << num_sec << "]" << endl//parte de abajo
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |" << endl;
		break;
		/*case 0:
		cout << setw(47) << "=====MayMen=====" << endl             
		<<"                                                                   " << endl
		<<"                                                |" << endl
		<<"                                                |  El numero puede estar entre" << endl
		<<"        ########################                |" << endl
		<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
		<<"        ##   Vidas Restantes  ##                |" << endl
		<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de arriba
		<<"        ##       " << (char)186 << "    " << (char)186 << "       ##                |      El numero era " << endl
		<<"        ##                    ##                |" << endl// parte media
		<<"        ##       " << (char)186 << "    " << (char)186 << "       ##                |  " << endl
		<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |           " << num_sec << endl//parte de abajo
		<<"        ##                    ##                |" << endl    
		<<"        ########################                |" << endl;
		break;*/
	case 1:
		cout << setw(47) << "=====MayMen=====" << endl             
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##                    ##                |" << endl//parte de arriba
			<<"        ##         " << (char)186 << "          ##                |" << endl
			<<"        ##                    ##                |" << endl// parte media
			<<"        ##         " << (char)186 << "          ##                |  Intento: " << 11-y << endl
			<<"        ##                    ##                |" << endl//parte de abajo
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	case 2:
		cout << setw(47) << "=====MayMen=====" << endl             
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de arriba
			<<"        ##            " << (char)186 << "       ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl// parte media
			<<"        ##       " << (char)186 << "            ##                |  Intento: " << 11-y << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de abajo
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	case 3:
		cout << setw(47) << "=====MayMen=====" << endl              
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de arriba
			<<"        ##            " << (char)186 << "       ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl// parte media
			<<"        ##            " << (char)186 << "       ##                |  Intento: " << 11-y << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de abajo
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	case 4:
		cout << setw(47) << "=====MayMen=====" << endl                       
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##                    ##                |" << endl//parte de arriba
			<<"        ##       " << (char)186 << "    " << (char)186 << "       ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl// parte media
			<<"        ##            " << (char)186 << "       ##                |  Intento: " << 11-y << endl
			<<"        ##                    ##                |" << endl//parte de abajo
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	case 5:
		cout << setw(47) << "=====MayMen=====" << endl            
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de arriba
			<<"        ##       " << (char)186 << "            ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl// parte media
			<<"        ##            " << (char)186 << "       ##                |  Intento: " << 11-y << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	case 6:
		cout << setw(47) << "=====MayMen=====" << endl          
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de arriba
			<<"        ##       " << (char)186 << "            ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl// parte media
			<<"        ##       " << (char)186 << "    " << (char)186 << "       ##                |  Intento: " << 11-y << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	case 7:
		cout << setw(47) << "=====MayMen=====" << endl              
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de arriba
			<<"        ##            " << (char)186 << "       ##                |" << endl
			<<"        ##                    ##                |" << endl// parte media
			<<"        ##            " << (char)186 << "       ##                |  Intento: " << 11-y << endl
			<<"        ##                    ##                |" << endl
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	case 8:
		cout << setw(47) << "=====MayMen=====" << endl               
			<<"                                                                  " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de arriba
			<<"        ##       " << (char)186 << "    " << (char)186 << "       ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl// parte media
			<<"        ##       " << (char)186 << "    " << (char)186 << "       ##                |  Intento: " << 11-y << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |"<< endl
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		
		break;
	case 9:
		cout << setw(47) << "=====MayMen=====" << endl              
			<<"                                                                   " << endl
			<<"                                                |" << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl//parte de arriba
			<<"        ##       " << (char)186 << "    " << (char)186 << "       ##                |" << endl
			<<"        ##        "<< (char)205 << (char)205 <<(char)205 << (char)205 << "        ##                |" << endl// parte media
			<<"        ##            " << (char)186 << "       ##                |  Intento: " << 11-y << endl
			<<"        ##                    ##                |" << endl//parte de abajo
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	case 10:
		cout << setw(47) << "=====MayMen=====" << endl            
			<<"                                                                   " << endl
			<<"                                                  " << endl
			<<"                                                |  El numero puede estar entre" << endl
			<<"        ########################                |" << endl
			<<"        ##                    ##                |        [" << men << " y " << may << "]" << endl
			<<"        ##   Vidas Restantes  ##                |" << endl
			<<"        ##            "<< (char)205 << (char)205 <<(char)205 << (char)205 << "    ##                |" << endl//parte de arriba
			<<"        ##     " << (char)186 << "     " << (char)186 << "    " << (char)186 << "   ##                |" << endl
			<<"        ##                    ##                |" << endl// parte media
			<<"        ##     " << (char)186 << "     " << (char)186 << "    " << (char)186 << "   ##                |  Intento: " << 11-y << endl
			<<"        ##            "<< (char)205 << (char)205 <<(char)205 << (char)205 << "    ##                |" << endl//parte de abajo
			<<"        ##                    ##                |" << endl    
			<<"        ########################                |  Ingrese un numero: ";
		break;
	}
}
void actualizar(int x, int& men, int& may, int y){
	if(x<may and x>y)
		may = x;
	else if(x>men and x<y)
		men = x;
}
bool seAcerto(int x, int y, int intentos){
	bool verdad=false;
	
	if(x==y)
		verdad=true;
	else if(intentos >= 10)
		verdad=true;
	
	return verdad;
}
