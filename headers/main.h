const int __MAX_USERS = 100;
const int __MAX_PARTIDAS = 1000;

struct Partidas {
	char nombre_usuario[11];
	int id_juego, puntaje_obtenido;
};
struct Premios {
	int diplomas, monedas, medallas, trofeos, copas, total;
};
struct Juegos {
	char nombre[15];
	char categoria[15];
};

struct Fecha {
	int dia;
	int mes;
	int anio;
	int hora;
	int min;
};

struct usuarios {
	char nombre[11];
	char contra[37];
	Fecha ultimo_acceso;
	Premios total[5];
};



bool esCorrectoUser(char []);
bool yaExiste(char [], usuarios registro[], int);
bool esCorrectaContra(char []);
bool estaValidada(char [], char []);

void iniciarSesion(usuarios registro[], Partidas partidas[], int, int&, int& partidas_totales, int[], int[]);
void registrarse(usuarios registro[], Partidas partidas[], int&, int&, int& partidas_totales, int[], int[]);

void levantarDatos(usuarios registro[], Partidas partidas[], int &id, int &partidas_totales);
void guardarDatos(usuarios registro[], Partidas partidas[], const int id, const int partidas_totales);

void MenudeUsuario(usuarios registro[], Partidas partidas[], int, int& partidas_totales, int[], int[]);
void menuJuegos(int opcion, usuarios registro[], Partidas partidas[], int id, int& partidas_totales, int[], int[]);
void nombreJuego(Juegos& juego, int opcion);
void instrucciones (int, Juegos);
void menuEstadisticas(int, Partidas[], usuarios[], int);
void medallero(int valores[5][5], int max[2][5]);

int retornoID(usuarios registro[], char [], int);
int cantDig(int x);

void setFullConsole();
