#include "Tablero.h"



int main()
{
	Tablero tablero;
	tablero.actualizarTablero();
	tablero.mover(Posicion{ 1,7 }, Posicion{ 1,5 });
	tablero.actualizarTablero();
	tablero.imprimeTablero();

	return 0;
}


