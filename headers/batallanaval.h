#include <cstdlib>
#include <ctime>
#include <cstddef>
#include <iomanip>
#include <Windows.h>

int batallaNaval();
void cargarTablero(char [][10]);
void cargarModificado(char [][10]);
void mostrarMatriz(char [][10]);
void imprimirPresentacion(char modificado[][10], int puntaje, int hundidos);
void compararTablero(char [][10],char [][10],int, int, int&, int&, int&);
void modificarExplosion(char tablero[][10], char modificado[][10], int y, int x, int tam);
int tamanioBarco(char);
bool hayBarco(char [][10],int, int, int);
bool posicionInvalida(int, int);
