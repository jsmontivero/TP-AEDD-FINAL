#include <cstdlib>
#include <ctime>
#include <cstddef>
#include <iomanip>
#include <Windows.h>

int adivinum();
bool chequearNumero(int);
int numeroSecreto();
bool cuatroCifras(int);
void cargarVector(int, int[]);
void comparar(int[], int[], int&, int&);
void interfaz_adivinum(int, int, int, int, int);

const int __MAX_TAM=4;
