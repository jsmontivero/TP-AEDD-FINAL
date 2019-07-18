#include <cstdlib>
#include <ctime>
#include <cstddef>
#include <iomanip>
#include <Windows.h>

int ahorcado();
int cantLetras(char v[]);
void cargarVector(char palabra[], char v[]);
void cargarGuiones(char v[], int);
void imprimirLog(char guiones[], char partes[10][17], char ingresadas[2][26], char palabra[], int, int);
bool esNumero(int);
bool seRepite (char, char y[2][26], int);
bool verificacion(char, char palabra[], int, int&, char guiones[]);
