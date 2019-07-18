#include <cstdlib>
#include <ctime>
#include <cstddef>
#include <iomanip>
#include <Windows.h>

int mayMen();
void interfaz_mayMen(int x, int men, int may, int y, int num_sec);
void actualizar(int x, int& men, int& may, int y);
bool seAcerto(int x, int y, int intentos);
