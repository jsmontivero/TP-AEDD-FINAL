#include <iostream>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <cctype>
#include <ctime>
#include <wincon.h>

#include "headers/colors.h"
#include "headers/adivinum.h"
#include "headers/ahorcado.h"
#include "headers/batallanaval.h"
#include "headers/maymen.h"
#include "headers/warcoin.h"

#include "headers/main.h"

#include <iomanip>
#include <fstream>

using namespace std;

int main(){	
	setFullConsole();
	
	print_char(0, 0, FOREGROUND_BLACK | BACKGROUND_WHITE | BACKGROUND_INTENSITY, 0, 1); // Fondo blanco con letras negras
	system("title Juegos2017");

	usuarios registro[__MAX_USERS];
	Partidas partidas[__MAX_PARTIDAS];
	
	int id=0, partidas_totales=0, mayor[5]={0,0,0,0,0}, cant_jugados[5]={0,0,0,0,0}, opcion;
	
	levantarDatos(registro, partidas, id, partidas_totales);
	do{
		

		
		system("cls");
		cout << "\n\n              Menu Principal       |      Cuentas Registradas: " << id << endl;
		cout << "       ------------------------------------------------------------" << endl;
		
		cout << "        1.- Registrarse" << endl;
		cout << "        2.- Iniciar Sesi" << char(162) << "n" << endl;
		cout << "        3.- Estadisticas" << endl;
		cout << "        9.- Cerrar la aplicacion" << endl << endl;
		
		cout << "       ------------------------------------------------------------" << endl;
		cout << "                           Ingrese una opcion: ";
		cin >> opcion;
		
		switch(opcion) {
			case 1: 
				registrarse(registro, partidas, id, opcion, partidas_totales, mayor, cant_jugados);
				break;
			case 2:
				iniciarSesion(registro, partidas, id, opcion, partidas_totales, mayor, cant_jugados);
				break;
			case 3:
				menuEstadisticas(partidas_totales, partidas, registro, id);
		};
	} while(opcion != 9);
	
	guardarDatos(registro, partidas, id, partidas_totales);
	return 0;
	
}

void iniciarSesion(usuarios registro[100], Partidas partidas[], int id, int& opcion, int& partidas_totales, int mayor[], int cant_jugados[]){
	
	int ID_PROPIO, intentos=1;
	char user[11], pass[37];
	
	/*-----parte de fecha de ingreso-----*/
	time_t ahora;
	struct tm *fecha;
	time(&ahora);
	fecha = localtime(&ahora);
	/*-------------------------------------*/
	
	system("cls");
	cout << "\n\n           Iniciando Sesi" << char(162) << "n   |        " << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;
	cout << "                  Ingrese su nombre de usuario: ";
	cin >> user;
	ID_PROPIO = retornoID(registro, user, id);
	
	while(ID_PROPIO == -1 and intentos<3) {
		system("cls");
		intentos++;
		cout << "\n\n           Iniciando Sesi" << char(162) << "n   |   ERROR - El usuario no existe" << endl;
		cout << "       ------------------------------------------------------------" << endl << endl;
		cout << "                  Ingrese su nombre de usuario: ";
		cin >> user;
		ID_PROPIO = retornoID(registro, user, id);
	}
	if(intentos==3){
		for(int i=0; i<30; i++){
			Sleep(120);
			system("cls");
			system("title ALERTA");
			if(i%2==0)
				system("color 4F");
			else
				system("color 1F");
			cout << "\a";
			if(i%4!=0){
			cout << endl << "       ------------------------------------------------------------" << endl
				<<          "                   **********************************              " << endl
				<<          "                   **ERROR - VIOLACION DE SEGURIDAD**              " << endl
				<<          "                   **********************************              " << endl
				<<          "       ------------------------------------------------------------" << endl << endl;
			}
		}
		opcion = 9;
		return;
	}
	
	system("cls");
	intentos=1;
	cout << "\n\n           Iniciando Sesi" << char(162) << "n   |     Usuario : " << user << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;
	cout << "                         Ingrese su contrase" << char(164) << "a: ";
	cin >> pass;
	
	while(strcmp(registro[ID_PROPIO].contra, pass) != 0 and intentos<3){
		system("cls");
		intentos++;
		cout << "\n\n           Iniciando Sesi" << char(162) << "n   |   ERROR - La contrase" << char(164) << "a es incorrecta" << endl;
		cout << "       ------------------------------------------------------------" << endl << endl;
		cout << "                         Ingrese su contrase" << char(164) << "a: ";
		cin >> pass;
	}
	if(intentos==3){
		system("cls");
		system("title ALERTA");
		for(int i=0; i<30; i++){
			
			Sleep(120);
			system("cls");
			if(i%2==0)
				system("color 4F");
			else
				system("color 1F");
			
			cout << "\a";
			cout << endl << "       ------------------------------------------------------------" << endl
			<<          "                    ********************************               " << endl
			<<          "                    *ERROR - VIOLACION DE SEGURIDAD*               " << endl
			<<          "                    ********************************               " << endl
			<<          "       ------------------------------------------------------------" << endl << endl;
		}
		opcion = 9;
		return;
	}
	
	system("cls");
	
	clock_t inicio, fin;
	double transcurrido;
	inicio = clock();
	
	MenudeUsuario(registro, partidas, ID_PROPIO,  partidas_totales, mayor, cant_jugados);
	
	fin = clock();
	
	transcurrido = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
	
	system("cls");
	cout << "             Saliendo de la sesion    |" << endl;
 	cout << "       ------------------------------------------------------------" << endl << endl;
	cout << "          Hasta luego " << registro[ID_PROPIO].nombre << "!!!" << endl;
	cout << "          Duracion de la sesion: ";
	cout << fixed << setprecision(1) << transcurrido/60 << " Minutos." << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;

	
	registro[ID_PROPIO].ultimo_acceso.dia = fecha->tm_mday;
	registro[ID_PROPIO].ultimo_acceso.mes = fecha->tm_mon+1;
	registro[ID_PROPIO].ultimo_acceso.anio = fecha->tm_year+1900;
	registro[ID_PROPIO].ultimo_acceso.hora = fecha->tm_hour;
	registro[ID_PROPIO].ultimo_acceso.min = fecha->tm_min;

	system("pause");
}

void MenudeUsuario(usuarios registro[100], Partidas partidas[], int id, int& partidas_totales, int mayor[], int cant_jugados[]) {
	
	char nombre[15], nombre2[15]; //uso dentro de funcion
	int cantidad_mayor=0, cant_mayor2=0, valor_i=-1, valor_i2=-1, mostrarPremios[5]={0,0,0,0,0}; // uso dentro de funcion
	
	
	for(int i=0; i<partidas_totales; i++){
		if(strcmp(partidas[i].nombre_usuario, registro[id].nombre)==0) {
			cant_jugados[partidas[i].id_juego]++;
			mayor[partidas[i].id_juego] += partidas[i].puntaje_obtenido;
		}
	}
	
	
	for(int i=0; i<5; i++){
		if(cant_jugados[i]>cant_mayor2){
			cant_mayor2 = cant_jugados[i];
			valor_i2=i;
		}
	}
	
	for(int i=0; i<5; i++){
		if(mayor[i]>cantidad_mayor){
			cantidad_mayor = mayor[i];
			valor_i=i;
		}
	}
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(j==0)
				mostrarPremios[j]+=registro[id].total[i].diplomas;
			else if(j==1)
				mostrarPremios[j]+=registro[id].total[i].monedas;
			else if(j==2)
				mostrarPremios[j]+=registro[id].total[i].medallas;
			else if(j==3)
				mostrarPremios[j]+=registro[id].total[i].trofeos;
			else if(j==4)
				mostrarPremios[j]+=registro[id].total[i].copas;
		}
	}
	
	
	switch(valor_i2){
		case -1:
			strcpy(nombre2, "---");
			break;
		case 0:
			strcpy(nombre2, "Numericos");
			break;
		case 1:
			strcpy(nombre2, "Numericos");
			break;
		case 2:
			strcpy(nombre2, "Numericos");
			break;
		case 3:
			strcpy(nombre2, "de Letras");
			break;
		case 4:
			strcpy(nombre2, "de Tablas");
			break;
	}
	
	switch(valor_i){
		case -1:
			strcpy(nombre, "---");
			break;
		case 0:
			strcpy(nombre, "MayMen");
			break;
		case 1:
			strcpy(nombre, "Adivinum");
			break;
		case 2:
			strcpy(nombre, "Warcoin");
			break;
		case 3:
			strcpy(nombre, "Ahorcado");
			break;
		case 4:
			strcpy(nombre, "BatallaNaval");
			break;
	}
	
	
	cout << "                    =======================================                     " << endl;
	cout << "                    |         Bienvenido " << registro[id].nombre << "         |" << endl;
	cout << "                    =======================================                     " << endl;
	cout << setfill('0');
	cout << "         - Ultimo Acceso: " << setw(2) << registro[id].ultimo_acceso.dia 
		<< "/" << setw(2) << registro[id].ultimo_acceso.mes << "/" << setw(2) << registro[id].ultimo_acceso.anio
		<< " - " << setw(2) << registro[id].ultimo_acceso.hora << ":" << setw(2) << registro[id].ultimo_acceso.min << endl;
	cout << "         - Categoria favorita de juegos:  " << nombre2 << endl;
	cout << "         - Juego con mayor puntaje:       " << nombre << endl;
	cout << "         - Premios obtenidos:      ";
	
	cout << setfill(' ');
	cout << "- ";
	if(mostrarPremios[0]>0) 
		cout << "DIPLOMAS (" << mostrarPremios[0] << ") - ";
	if(mostrarPremios[1]>0) 
		cout << "MONEDAS (" << mostrarPremios[1] << ") - ";
	if(mostrarPremios[2]>0) 
		cout << "MEDALLAS (" << mostrarPremios[2] << ") - ";
	if(mostrarPremios[3]>0) 
		cout << "TROFEOS (" << mostrarPremios[3] << ") - ";
	if(mostrarPremios[4]>0) 
		cout << "COPAS (" << mostrarPremios[4] << ") - ";
	cout  << endl;
	
	cout << "       ------------------------------------------------------------" << endl;
	system("pause");
	int opcion;
	do {
		system("cls");
		cout << "\n              Menu de Juegos       |     Usuario : " << registro[id].nombre << endl;
		cout << "       ------------------------------------------------------------" << endl << endl;
		
		cout << "       Juegos Numericos" << endl;
		cout << "       ----------------" << endl;
		cout << "          1.- MayMen" << endl;
		cout << "          2.- Adivinum" << endl;
		cout << "          3.- WarCoin" << endl << endl;
		
		
		cout << "       Juegos de Letras" << endl;
		cout << "       ----------------" << endl;
		cout << "          4.- Ahorcado" << endl << endl;
		
		cout << "       Juegos con Tablas" << endl;
		cout << "       -----------------" << endl;
		cout << "          5.- Batalla Naval" << endl << endl;
		
		cout << "        9.- Cerrar Sesi" << char(162) << "n" << endl << endl;
		
		cout << "       ------------------------------------------------------------" << endl;
		cout << "                           Ingrese una opcion: ";
		cin >> opcion;
		
		switch(opcion) {
			case 9:
				break;
			default: // caso del 1 al 5
				menuJuegos(opcion, registro, partidas, id,  partidas_totales, mayor, cant_jugados);
				break;
		}
	} while(opcion != 9);
	
	
}
void menuJuegos(int opcion_ant, usuarios registro[], Partidas partidas[], int id,  int& partidas_totales, int mayor[], int cant_jugados[]) {
	system("cls");
	Juegos juego;
	nombreJuego(juego,opcion_ant);
	int opcion;
	cout << setfill(' ');
	if(strcmp(juego.nombre, "Adivinum") == 0)
		opcion_ant = 3;
	else if(strcmp(juego.nombre, "WarCoin") == 0)
		opcion_ant = 2;
	
	do {
		system("cls");
		cout << "\n           Juego - " << juego.nombre << "      |      Categoria - " << juego.categoria << endl;
		cout << "       ------------------------------------------------------------" << endl << endl;
		cout << "        1.- Instrucciones" << endl;
		cout << "        2.- Jugar" << endl;
		cout << "        3.- Ver Puntaje" << endl;
		cout << "        4.- Ver Premios" << endl;
		cout << "        9.- Volver al Menu de Juegos" << endl;
		cout << "       ------------------------------------------------------------" << endl;
		cout << "                           Ingrese una opcion: ";
		cin >> opcion;
		system("cls");
		switch(opcion) {
			case 1:
				if(strcmp(juego.nombre, "MayMen") == 0)
					instrucciones(0, juego);
				else if(strcmp(juego.nombre, "WarCoin") == 0)
						instrucciones(1, juego);
				else if(strcmp(juego.nombre, "Adivinum") == 0)
						instrucciones(2, juego);
				else if(strcmp(juego.nombre, "Ahorcado") == 0)
						instrucciones(3, juego);
				else if(strcmp(juego.nombre, "BatallaNaval") == 0)
						instrucciones(4, juego);
				
				system("pause");
				break;
			case 2:
				if(strcmp(juego.nombre, "MayMen") == 0){ // Juego.nombre es el nombre del juego que selecciono y juego.categoria es la categoria
					partidas[partidas_totales].id_juego = 0;
					partidas[partidas_totales].puntaje_obtenido = mayMen();
					if(partidas[partidas_totales].puntaje_obtenido >= 2 && partidas[partidas_totales].puntaje_obtenido < 4)
						registro[id].total[0].diplomas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 4 && partidas[partidas_totales].puntaje_obtenido < 6)
						registro[id].total[0].monedas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 6 && partidas[partidas_totales].puntaje_obtenido < 8)
						registro[id].total[0].medallas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 8 && partidas[partidas_totales].puntaje_obtenido < 10)
						registro[id].total[0].trofeos++;
					
					else if(partidas[partidas_totales].puntaje_obtenido == 10)
						registro[id].total[0].copas++;
					
					if(partidas[partidas_totales].puntaje_obtenido > mayor[0])
						mayor[0] = partidas[partidas_totales].puntaje_obtenido;
					
					cant_jugados[0]++;
				}
				else if(strcmp(juego.nombre, "WarCoin") == 0){
					partidas[partidas_totales].id_juego = 1;
					partidas[partidas_totales].puntaje_obtenido = warCoin();
					if(partidas[partidas_totales].puntaje_obtenido >= 2 && partidas[partidas_totales].puntaje_obtenido < 4)
						registro[id].total[1].diplomas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 4 && partidas[partidas_totales].puntaje_obtenido < 6)
						registro[id].total[1].monedas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 6 && partidas[partidas_totales].puntaje_obtenido < 8)
						registro[id].total[1].medallas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 8 && partidas[partidas_totales].puntaje_obtenido < 10)
						registro[id].total[1].trofeos++;
					
					else if(partidas[partidas_totales].puntaje_obtenido == 10)
						registro[id].total[1].copas++;
					
					if(partidas[partidas_totales].puntaje_obtenido > mayor[1])
						mayor[1] = partidas[partidas_totales].puntaje_obtenido;
					cant_jugados[1]++;
				}
				else if(strcmp(juego.nombre, "Adivinum") == 0){
					partidas[partidas_totales].id_juego = 2;
					partidas[partidas_totales].puntaje_obtenido = adivinum();
					
					if(partidas[partidas_totales].puntaje_obtenido == 1 )
						registro[id].total[2].diplomas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido == 2)
						registro[id].total[2].monedas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido == 3)
						registro[id].total[2].medallas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido == 4)
						registro[id].total[2].trofeos++;
					
					else if(partidas[partidas_totales].puntaje_obtenido == 5)
						registro[id].total[2].copas++;
					
					if(partidas[partidas_totales].puntaje_obtenido > mayor[2])
						mayor[2] = partidas[partidas_totales].puntaje_obtenido;
					cant_jugados[2]++;
				}
				else if(strcmp(juego.nombre, "Ahorcado") == 0){
					partidas[partidas_totales].id_juego = 3;
					partidas[partidas_totales].puntaje_obtenido = ahorcado();
					
					if(partidas[partidas_totales].puntaje_obtenido >= 10 && partidas[partidas_totales].puntaje_obtenido < 20)
						registro[id].total[3].diplomas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 20 && partidas[partidas_totales].puntaje_obtenido < 30)
						registro[id].total[3].monedas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 30 && partidas[partidas_totales].puntaje_obtenido < 40)
						registro[id].total[3].medallas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 40 && partidas[partidas_totales].puntaje_obtenido < 50)
						registro[id].total[3].trofeos++;
					
					else if(partidas[partidas_totales].puntaje_obtenido == 50)
						registro[id].total[3].copas++;
					
					if(partidas[partidas_totales].puntaje_obtenido > mayor[3])
						mayor[3] = partidas[partidas_totales].puntaje_obtenido;
					
					cant_jugados[3]++;
				}
				else if(strcmp(juego.nombre, "BatallaNaval") == 0){
					partidas[partidas_totales].id_juego = 4;
					partidas[partidas_totales].puntaje_obtenido = batallaNaval();
					
					if(partidas[partidas_totales].puntaje_obtenido >= 20 && partidas[partidas_totales].puntaje_obtenido < 40)
						registro[id].total[4].diplomas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 40 && partidas[partidas_totales].puntaje_obtenido < 60)
						registro[id].total[4].monedas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 60 && partidas[partidas_totales].puntaje_obtenido < 80)
						registro[id].total[4].medallas++;
					
					else if(partidas[partidas_totales].puntaje_obtenido >= 80 && partidas[partidas_totales].puntaje_obtenido < 90)
						registro[id].total[4].trofeos++;
					
					else if(partidas[partidas_totales].puntaje_obtenido == 90)
						registro[id].total[4].copas++;
					if(partidas[partidas_totales].puntaje_obtenido > mayor[4])
						mayor[4] = partidas[partidas_totales].puntaje_obtenido;
					cant_jugados[4]++;
				}
				strcpy(partidas[partidas_totales].nombre_usuario, registro[id].nombre);
				partidas_totales++;
				break;
			case 3:	
				system("cls");
				cout << "\n     Accediendo a evolucion de " << registro[id].nombre << "      |      " << juego.nombre << endl;
					cout << "       ------------------------------------------------------------" << endl << endl;
				if(strcmp(juego.nombre, "MayMen") == 0){
					cout << "       Jugo " << cant_jugados[0] << " veces" << endl
						<< "       El mayor puntaje obtenido fue de " << mayor[0] << " puntos" << endl;
				}
				else if(strcmp(juego.nombre, "WarCoin") == 0){
					cout << "       Jugo " << cant_jugados[1] << " veces" << endl
						<< "       El mayor puntaje obtenido fue de " << mayor[1] << " puntos" << endl;
				}
				else if(strcmp(juego.nombre, "Adivinum") == 0){
					cout << "       Jugo " << cant_jugados[2] << " veces" << endl
						<< "       El mayor puntaje obtenido fue de " << mayor[2] << " puntos" << endl;
				}
				else if(strcmp(juego.nombre, "Ahorcado") == 0){
					cout << "       Jugo " << cant_jugados[3] << " veces" << endl
						<< "       El mayor puntaje obtenido fue de " << mayor[3] << " puntos" << endl;
				}
				else if(strcmp(juego.nombre, "BatallaNaval") == 0){
					cout << "       Jugo " << cant_jugados[4] << " veces" << endl
						<< "       El mayor puntaje obtenido fue de " << mayor[4] << " puntos" << endl;
				}
				cout << "       ------------------------------------------------------------" << endl;
				system("pause");
				break;
			case 4:	
				system("cls");
				cout << "\n       Premios obtenidos en " << juego.nombre << "    |      " << endl;
				cout << "       ------------------------------------------------------------" << endl << endl;
				cout << "          Diplomas:   " << registro[id].total[opcion_ant-1].diplomas << endl
					<< "          Monedas:    " << registro[id].total[opcion_ant-1].monedas << endl
					<< "          Medallas:   " << registro[id].total[opcion_ant-1].medallas << endl
					<< "          Trofeos:    " << registro[id].total[opcion_ant-1].trofeos << endl
					<< "          Copas:      " << registro[id].total[opcion_ant-1].copas << endl;
				system("pause");
				break;
		}
	} while(opcion != 9);
}
void nombreJuego(Juegos& juego, int opcion) {
	if(opcion == 1)
		strcpy(juego.nombre, "MayMen");
	else if(opcion == 2)
		strcpy(juego.nombre, "Adivinum");
	else if(opcion == 3)
		strcpy(juego.nombre, "WarCoin");
	else if(opcion == 4) {
		strcpy(juego.nombre, "Ahorcado");
		strcpy(juego.categoria, "de Letras");
	}
	else if(opcion == 5) {
		strcpy(juego.nombre, "BatallaNaval");
		strcpy(juego.categoria, "con Tablas");
	}
	
	if(opcion >= 1 && opcion <= 3)
		strcpy(juego.categoria, "Numericos");
}
void registrarse(usuarios registro[100], Partidas partidas[], int &id, int& opcion, int& partidas_totales, int mayor[], int cant_jugados[]) {
	char user[11], pass[37], pass_validar[37], siOno;
	/* Se registra el usuario */
	system("cls");
	cout << "\n\n            Registrando Usuario    |" << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;	
	cout << "                         Ingrese un usuario: ";
	cin >> user;
	while(!esCorrectoUser(user) or yaExiste(user, registro, id)) {
		system("cls");
		if(!esCorrectoUser(user)){
			cout << "\n\n            Registrando Usuario    |     ERROR - Usuario incorrecto" << endl;
			cout << "       ------------------------------------------------------------" << endl << endl;
			cout << "                         Ingrese un usuario: ";
			cin >> user;
			cin.ignore();
		}
		else if(yaExiste(user, registro, id)){
			cout << "\n\n          Registrando Usuario      |   ERROR - Usuario ya registrado" << endl;
			cout << "       ------------------------------------------------------------" << endl << endl;
			cout << "                         Ingrese un usuario: ";
			cin >> user;
			cin.ignore();
		}
	}

	

	
	/* Se registra la contraseña */
	system("cls");
	cout << "\n\n            Registrando Password    |" << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;
	cout << "                         Ingrese una contrase" << (char)164 << "a: ";
	
	
	cin >> pass;
	while(!esCorrectaContra(pass)){
		system("cls");
		cout << "\n\n             Registrando Password    |    ERROR - Contrase" << (char)164 << "a incorrecta" << endl;
		cout << "       ------------------------------------------------------------" << endl << endl;
		cout << "                         Ingrese una contrase" << (char)164 << "a: ";
		cin >> pass;
	}

	
	/* Se valida la contraseña */
	system("cls");
	cout << "\n\n            Validando Password    |" << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;
	cout << "                          Ingrese su contrase" << char(164) << "a: ";
	cin >> pass_validar;
	
	while(!estaValidada(pass, pass_validar)){
		system("cls");
		cout << "\n\n             Validando Password    |    ERROR - Contrase" << (char)164 << "a incorrecta" << endl;
		cout << "       ------------------------------------------------------------" << endl << endl;
		cout << "                          Ingrese su contrase" << char(164) << "a: ";
		cin >> pass_validar;
	}
	
	strcpy(registro[id].nombre, user);
	strcpy(registro[id].contra, pass);
	
	system("cls");
	cout << "\n\n            Validando Password    |    Su password es: " << pass << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;
	cout << "                          Contrase" << (char)164 << "a v" << (char)160 << "lida" << endl;
	Sleep(1500);
	id++;
	
	for(int i = 0; i < 5; i++) {
		registro[id].total[i].copas = 0;
		registro[id].total[i].medallas = 0;
		registro[id].total[i].trofeos = 0;
		registro[id].total[i].diplomas = 0;
		registro[id].total[i].monedas = 0;
	}
	
	system("cls");
	cout << "\n\n              Inicio de Sesion    |" << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;
	
	cout << "                       Desea inciar sesion? (S/N) ";
	
	
	cin >> siOno;
	if(toupper(siOno)=='S')
		iniciarSesion(registro, partidas, id, opcion,  partidas_totales, mayor, cant_jugados);
}
bool esCorrectoUser(char user[11]) {
	bool check=true;
	
	if(strlen(user) < 6 or strlen(user) > 10)
		check = false;
	
	if(check && !islower(user[0]))
		check = false;
	
	if(check) {
		int mayusculas=0, digitos = 0, i = 0;
		while(mayusculas < 2 && digitos < 4 && i < int(strlen(user))) {
			if(isupper(user[i]))
				mayusculas++;
			else if(isdigit(user[i]))
				digitos++;
			
			i++;
		}
		if(mayusculas < 2 || digitos >= 4)
			check = false;
	}
	
	return check;
}
bool esCorrectaContra(char x[37]) {
	bool min=false, may=false, num=false, check=true;
	int cant_consecutivos=0, i=0, tam, j=0;
	
	tam = strlen(x);
	
	if(tam < 6 or tam > 32)
		check = false;
	
	while(i<tam and check){
		if(isalpha(x[i]) and isalpha(x[i+1]) and tolower(x[i])+1 == tolower(x[i+1]) and i < tam-1)
			check = false;
		
		if (x[i]>='a' and x[i]<='z')
			min=true;
		else if(x[i]>='A' and x[i]<='Z')
			may=true;
		else if(x[i]>=48 and x[i]<=57)
			num=true;
		else
			check = false;
		
		i++;
	}
	
	
	while(check and cant_consecutivos<=3 and j<tam){
		if(isdigit(x[j]))
			cant_consecutivos++;
		else 
			cant_consecutivos = 0;
		j++;
	}
	
	if(min and may and num and cant_consecutivos!=3)
		  return true;
	else
		return false;
}
bool estaValidada(char x[37], char y[37]){
	
	int i=0, check=0, tam1, tam2;
	
	tam1 = (int)strlen(x);
	tam2 = (int)strlen(y);
	
	if(tam1==tam2){
		while(i<tam1){
			
			if(x[i]==y[i])
				check++;
			
			i++;
		}
	}
	
	if(check==tam1)
	   return true;
	else
		return false;
}

bool yaExiste(char user[11], usuarios registro[100], int id){
	
	int i=0;
	bool check=false;
	
	while(!check and i<id){
		if(strcmp(user, registro[i].nombre) == 0)
			check=true;
		
		i++;
	}
	
	return check;
	
}

int retornoID(usuarios registro[100], char user[11], int id) {
	int i = 0;
	bool searched = false;
	while(i < id && !searched) {
		if(strcmp(user, registro[i].nombre) == 0)
			searched = true;
		else
			i++;
	}
	
	if(!searched)
		i = -1;
	
	return i;
}
void instrucciones(int caso, Juegos juego){
	system("cls");
	cout << "\n           Juego - " << juego.nombre << "      |      Categoria - " << juego.categoria << endl;
	cout << "       ------------------------------------------------------------" << endl << endl;
	switch(caso){
		
	case 0:
		cout << "       Consiste en adivinar un numero que esta entre 1 y 999." << endl
			<< "       El jugador, en cada intento ingresa un numero" << endl
			<<  "       y ganara la partida si antes de superar los 10 intentos" << endl
			<<  "       adivina el numero secreto." << endl;
			break;
	case 1:
		cout <<   "       Se tiene que adivinar un num de 4 cifras, donde c/digito aparece 1 vez como maximo." << endl
			<<   "       Teniendo 10 intentos se informara, cuantos digitos estaban en una posicion correcta" << endl
			<<  "       y cuantos en una diferente." << endl;
		break;
	case 2:
		cout <<  "       Consiste en una pila de monedas, de la cual el jugador y la computadora van sacando monedas" << endl
			<< "       hasta que ya no quedan mas en la pila. El que vacia la pila de monedas es quien gana el juego." << endl;
		break;
	case 3:
		cout <<  "       El usuario ingresa secuencialmente un caracter a fin de adivinar la palabra de juego." << endl
			<< "       Una vez agotadas las partes del cuerpo, provocara el estado de ahorcado" << endl
			<< "       y, en consecuencia, se perdera la partida." << endl;
		break;
	case 4:
		cout <<  "       Este juego es una version modificada del clasico batalla naval. El objetivo del juego es" << endl
			<<  "       hundir la flota enemiga lo mas rapido posible y evitando las minas." << endl;
		break;
	}
	cout << "       ------------------------------------------------------------" << endl;
}

void menuEstadisticas(int partidas_totales, Partidas partidas[], usuarios registro[], int total_users){
	
	int opcion, opcion2, masJugado[5], masJugadoTemp[5]={0}, masJugado_mayor, menosJugado, masGanadores[total_users][5];
	for(int i=0; i<partidas_totales; i++){
		masJugadoTemp[partidas[i].id_juego]++;
	}
	
	int id_nuevo[5]= {0}, total, max[5] = {0 };
	
	for(int j = 0; j < 5; j++) {
		max[j] = registro[0].total[j].diplomas + registro[0].total[j].copas +  registro[0].total[j].medallas +  registro[0].total[j].monedas + registro[0].total[j].trofeos;
		id_nuevo[0] = 0;
	}
	
	for(int i = 0; i < total_users; i++) {
		for(int j = 0; j < 5; j++) {
			total = registro[i].total[j].diplomas + registro[i].total[j].copas +  registro[i].total[j].medallas +  registro[i].total[j].monedas + registro[i].total[j].trofeos;
			if(total > max[j]) {
				max[j] = total;
				id_nuevo[j] = i;
			}
		}
	}
	
	int valor[5][5] = { 0, 0, 0, 0, 0 };
	int maxMedallero[2][5] = { 0, 0, 0, 0, 0 };
	int maxI, maxJ;
	
	for(int j = 0; j < 5; j++) 
	{
		for(int i = 0; i < total_users; i++) {
			valor[j][0] += registro[i].total[j].diplomas;
			valor[j][1] += registro[i].total[j].monedas;
			valor[j][2] += registro[i].total[j].medallas;
			valor[j][3] += registro[i].total[j].trofeos;
			valor[j][4] += registro[i].total[j].copas;
		}
	}
	
	/* Medallero - Calcula el maximo de cada columna por fila y de cada fila por columna */
	for(int i = 0; i < 5; i++) {
		maxI = valor[i][0];
		maxJ = valor[0][i];
		
		for(int j = 0; j < 5; j++) {
			if(valor[i][j] > maxI)
				maxI = j;
				
			if(valor[i][j] > maxJ)
				maxJ = i;
		}
		
		maxMedallero[0][i] = maxI; // En este vector guardamos la posicion I (el juego)
		maxMedallero[1][i] = maxJ; // En este vector guardamos la posicion J (el premio)
	}
	
	for(int i=0; i<total_users; i++)
		for(int j=0; j<5; j++)
			masGanadores[i][j]=0;
		
		
	for (int i=0; i<total_users; i++){
		for(int j=0; j<5; j++){
			masGanadores[i][0]+=registro[i].total[j].diplomas;
			masGanadores[i][1]+=registro[i].total[j].monedas;
			masGanadores[i][4]+=registro[i].total[j].copas;
			masGanadores[i][2]+=registro[i].total[j].medallas;
			masGanadores[i][3]+=registro[i].total[j].trofeos;
		}
	}
	
	do {
		system("cls");
		cout << "\n\n              Estadisticas       |" << endl;
		cout << "       ------------------------------------------------------------" << endl;
		
		cout << "       De juegos" << endl;
		cout << "       ----------------" << endl;
		cout << "          1.- Ranking de juegos mas jugado" << endl;
		cout << "          2.- Juego menos jugado" << endl;
		cout << "          3.- Medallero olimpico" << endl << endl;
		
		cout << "       De usuarios" << endl;
		cout << "       ----------------" << endl;
		cout << "          4.- Mejor jugador de cada juego" << endl;
		cout << "          5.- Top3 jugadores con mas premios" << endl << endl;
		
		
		cout << "        9.- Volver" << endl;
		cout << "       ------------------------------------------------------------" << endl;
		cout << "                           Ingrese una opcion: ";
		cin >> opcion;
		

		switch(opcion) {
			case 1:
				system("cls");
				cout << "\n\n              Estadisticas     |    Ranking de juegos mas jugado" << endl;
				cout << "       ------------------------------------------------------------" << endl;
				
				for(int n=0; n<5; n++){
					masJugado[n] = masJugadoTemp[n];
				}
				masJugado_mayor=masJugado[0];
				
				
				for(int i=0; i<5; i++){
					for(int j=0; j<5; j++){
						if(masJugado[j]>masJugado[masJugado_mayor])
							masJugado_mayor=j;
					}
					
					cout << "          " << i+1 << ". ";
					if(masJugado_mayor==0)
						cout << "MayMen ";
					else if(masJugado_mayor==1)
						cout << "WarCoin ";
					else if(masJugado_mayor==2)
						cout << "Adivinum ";
					else if(masJugado_mayor==3)
						cout << "Ahorcado ";
					else if(masJugado_mayor==4)
						cout << "Batalla Naval ";
						
					cout << " - " << masJugado[masJugado_mayor] << " veces." << endl;
					masJugado[masJugado_mayor]=-1;
				}
				cout << "       ------------------------------------------------------------" << endl;
				break;
			case 2:
				system("cls");
				cout << "\n\n              Estadisticas     |    Juego menos jugado" << endl;
				cout << "       ------------------------------------------------------------" << endl;
				
				for(int n=0; n<5; n++){
					masJugado[n] = masJugadoTemp[n];
				}
				menosJugado=masJugado[0];
				
				for(int i=0; i<5; i++){
					for(int j=0; j<5; j++){
						if(masJugado[j]<=masJugado[menosJugado])
							menosJugado=j;
					}
				}
				cout << "          El juego menos jugado es ";
					if(menosJugado==0)
						cout << "MayMen ";
					else if(menosJugado==1)
						cout << "WarCoin ";
					else if(menosJugado==2)
						cout << "Adivinum ";
					else if(menosJugado==3)
						cout << "Ahorcado ";
					else if(menosJugado==4)
						cout << "Batalla Naval ";
					cout << "\n       ------------------------------------------------------------" << endl;
				break;
			case 3:
				medallero(valor, maxMedallero);
				break;
			case 4:
				system("cls");
				cout << "\n\n              Estadisticas     |    Juego menos jugado" << endl;
				cout << "       ------------------------------------------------------------" << endl;
				
				for(int i = 0; i < 5; i++) {
					cout << "          El mejor jugador del juego ";
					if(i==0)
						cout << "MayMen ";
					else if(i==1)
						cout << "WarCoin ";
					else if(i==2)
						cout << "Adivinum ";
					else if(i==3)
						cout << "Ahorcado ";
					else if(i==4)
						cout << "Batalla Naval ";
					
					cout << " es " << registro[id_nuevo[i]].nombre << " con " << max[i] << " premios." << endl;
					
				}
				cout << "       ------------------------------------------------------------" << endl;
				break;
			case 5:
				
				system("cls");
				cout << "\n\n              Estadisticas     |     TOP 3 - Por premio" << endl;
				cout << "       ------------------------------------------------------------" << endl;
				cout << "         1. DIPLOMAS" << endl
					<< "         2. MONEDAS" << endl
					<< "         3. MEDALLAS" << endl
					<< "         4. TROFEOS" << endl
					<< "         5. COPAS" << endl;
				cout << "       ------------------------------------------------------------" << endl;
				cout << "       Ingrese una opcion: ";
				cin >> opcion2;
				
				system("cls");
				cout << "\n\n              Estadisticas     |     TOP 3 - Por premio" << endl;
				cout << "       ------------------------------------------------------------" << endl;
				
				if(total_users < 3)
					cout << endl << "          La cantidad de usuarios es minima para realizar un TOP3" << endl << endl;
				
				else{
					int id2 = 0;
					for(int i=0; i<3; i++){
						for(int j=0; j<total_users;	j++){
							if(masGanadores[j][opcion2-1]>masGanadores[id2][opcion2-1])
								id2=j;
						}
						cout << "         " << i << ". " << registro[id2].nombre << " con " << masGanadores[id2][opcion2-1];
						if(opcion2-1==0)
							cout << " DIPLOMAS." << endl;
						else if(opcion2-1==1)
							cout << " MONEDAS." << endl;
						else if(opcion2-1==2)
							cout << " MEDALLAS." << endl;
						else if(opcion2-1==3)
							cout << " TROFEOS." << endl;
						else if(opcion2-1==4)
							cout << " COPAS." << endl;
						masGanadores[id2][opcion2-1]=-1;
						
					}
				}
				cout << "       ------------------------------------------------------------" << endl;
				
				for(int i=0; i<total_users; i++)
					for(int j=0; j<5; j++)
						masGanadores[i][j]=0;
					
					
				break;
		}
		if(opcion != 9 && opcion != 3)
			system("pause");
		
	} while(opcion != 9);
}

void medallero(int valor[5][5], int max[2][5]){
	int opcion = 1;
	do {
		system("cls");
		cout << "\n\n                   Medallero                  |       " << endl;
		cout << "       +------------------------------------------------------------------------+" << endl
			<< "       |            |                          Premios                          |" << endl
			<< "       |   Juego    +-----------------------------------------------------------|" << endl
			<< "       |            |  DIPLOMAS |  MONEDAS  |  MEDALLAS |  TROFEOS  |   COPAS   |" << endl
			<< "       +------------+-----------+-----------+-----------+-----------+-----------|" << endl
			<< "       |   Maymen   |";
		
		for(int i = 0; i < 5; i++) {
			cout << "   " << setw(4-cantDig(valor[0][i])) << " ";
			
			if(max[0][0] == i && opcion == 1)
				print_char(valor[0][i], 1, FOREGROUND_INTENSE_RED | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 1, 0);
			
			else if(max[1][i] == 0 && opcion == 2)
				print_char(valor[0][i], 1, FOREGROUND_INTENSE_BLUE | FOREGROUND_INTENSITY | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN) | BACKGROUND_INTENSITY, 1, 0);
			else
				cout << valor[0][i];
				
				cout << "   " << ((i<4) ? " |" : " | \n");
		}
		
		cout << "       +------------+-----------+-----------+-----------+-----------+-----------|" << endl
		<< "       |  WarCoin   |";
		for(int i = 0; i < 5; i++) {
			cout << "   " << setw(4-cantDig(valor[1][i])) << " ";
			
			if(max[0][1] == i && opcion == 1)
				print_char(valor[1][i], 1, FOREGROUND_INTENSE_RED | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 1, 0);
			
			else if(max[1][i] == 1 && opcion == 2)
				print_char(valor[1][i], 1, FOREGROUND_INTENSE_BLUE | FOREGROUND_INTENSITY | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN) | BACKGROUND_INTENSITY, 1, 0);
			else
				cout << valor[1][i];
				
				cout << "   " << ((i<4) ? " |" : " | \n");
		}
		
		cout << "       +------------+-----------+-----------+-----------+-----------+-----------|" << endl
		<< "       |  Adivinum  |";
		for(int i = 0; i < 5; i++) {
			cout << "   " << setw(4-cantDig(valor[2][i])) << " ";
			
			if(max[0][2] == i && opcion == 1)
				print_char(valor[2][i], 1, FOREGROUND_INTENSE_RED | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 1, 0);
			
			else if(max[1][i] == 2 && opcion == 2)
				print_char(valor[2][i], 1, FOREGROUND_INTENSE_BLUE | FOREGROUND_INTENSITY | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN) | BACKGROUND_INTENSITY, 1, 0);
			else
				cout << valor[2][i];
				
				cout << "   " << ((i<4) ? " |" : " | \n");
		}
			
		cout << "       +------------+-----------+-----------+-----------+-----------+-----------|" << endl
		<< "       |  Ahorcado  |";
		
		for(int i = 0; i < 5; i++) {
			cout << "   " << setw(4-cantDig(valor[3][i])) << " ";
			
			if(max[0][3] == i && opcion == 1)
				print_char(valor[3][i], 1, FOREGROUND_INTENSE_RED | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 1, 0);
			
			else if(max[1][i] == 3 && opcion == 2)
				print_char(valor[3][i], 1, FOREGROUND_INTENSE_BLUE | FOREGROUND_INTENSITY | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN) | BACKGROUND_INTENSITY, 1, 0);
			else
				cout << valor[3][i];
				
				cout << "   " << ((i<4) ? " |" : " | \n");
		}
		
		cout << "       +------------+-----------+-----------+-----------+-----------+-----------|" << endl
		<< "       |  B. Naval  |";
		for(int i = 0; i < 5; i++) {
			cout << "   " << setw(4-cantDig(valor[4][i])) << " ";
			
			if(max[0][4] == i && opcion == 1)
				print_char(valor[4][i], 1, FOREGROUND_INTENSE_RED | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 1, 0);
			
			else if(max[1][i] == 4 && opcion == 2)
				print_char(valor[4][i], 1, FOREGROUND_INTENSE_BLUE | FOREGROUND_INTENSITY | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN) | BACKGROUND_INTENSITY, 1, 0);
			else
				cout << valor[4][i];
				
				cout << "   " << ((i<4) ? " |" : " | \n");
		}
		
		cout << "       +------------------------------------------------------------------------+" << endl << endl << endl;
		
		cout << "                        1.- Ranking de juegos por premio ";
		if(opcion == 1) {
			print_char('(', 1, FOREGROUND_INTENSE_RED | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 0, 1);
			cout << "ACTUAL";
			print_char(')', 1, FOREGROUND_INTENSE_RED | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 1, 1);
		}
		cout << endl;
		cout << "                        2.- Ranking de premios por juego ";
		
		if(opcion == 2) {
			print_char('(', 1, FOREGROUND_INTENSE_BLUE | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 0, 1);
			cout << "ACTUAL";
			print_char(')', 1, FOREGROUND_INTENSE_BLUE | (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY), 1, 1);
		}
		cout << endl << endl;
		
		cout << "                    9.- Volver" << endl << endl;
		cout << "                   ------------------------------------------------------------" << endl;
		cout << "                                      Ingrese una opcion: ";
		cin >> opcion;
		
	} while(opcion != 9);
}

void levantarDatos(usuarios registro[], Partidas partidas[], int &id, int &partidas_totales) {
	fstream levantar;	
	levantar.open("usuarios.dat", ios::in | ios::binary);//guardamos en texto solamente los datos de usuarios
	if(levantar.good()) {
		levantar.read(reinterpret_cast<char *>(&registro[id]), sizeof(usuarios));
		while(!levantar.eof()) {
			id++;
			levantar.read(reinterpret_cast<char *>(&registro[id]), sizeof(usuarios));
		}
	}
	levantar.close();
	
	
	levantar.open("partidas.dat", ios::in | ios::binary);//vamos desde el struct usuarios, que tiene adentro todas las partidas
	if(levantar.good()) {
		levantar.read(reinterpret_cast<char *>(&partidas[partidas_totales]), sizeof(Partidas));
		while(!levantar.eof()){
			partidas_totales++;
			levantar.read(reinterpret_cast<char *>(&partidas[partidas_totales]), sizeof(Partidas));
		}
	}
	levantar.close();
}

void guardarDatos(usuarios registro[], Partidas partidas[], const int id, const int partidas_totales) {
	fstream guardar;
	
	guardar.open("usuarios.dat", ios::out | ios::binary);
	for(int i = 0; i < id; i++)
		guardar.write(reinterpret_cast<char *>(&registro[i]), sizeof(usuarios));
	
	guardar.close();
	
	guardar.open("partidas.dat", ios::out | ios::binary);
	for(int i = 0; i < partidas_totales; i++)
		guardar.write(reinterpret_cast<char *>(&partidas[i]), sizeof(Partidas));
	
	guardar.close();
}

void setFullConsole() {
	system("mode con: cols=1280 lines=1024");
	ShowWindow(GetConsoleWindow(),SW_MAXIMIZE); // Maximiza la consola
}

int cantDig(int x) {
	if(x < 10)
		return 1;
	
	return 1 + cantDig(x/10);
}
