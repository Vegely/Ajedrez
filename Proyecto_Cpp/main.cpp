#include "Tablero.h"
#include <iostream>


int main()
{
	Tablero tablero; //Creación del tablero con las piezas


	//TEST UNITARIO PARA VER SI MUEVEN Y COMEN LAS PIEZAS
	////////////////////////////////////////////////////////////
	tablero.mover(Posicion{ 1,0 }, Posicion{ 2,2 });
	tablero.mover(Posicion{ 1,6 }, Posicion{ 1,4 });
	tablero.mover(Posicion{ 2,2 }, Posicion{ 1,4 });
	tablero.mover(Posicion{ 2,2 }, Posicion{ 1,4 });
	tablero.mover(Posicion{ 1,4 }, Posicion{ 2,6 });
	tablero.imprimeTablero();
	////////////////////////////////////////////////////////////


	return 0;
}


