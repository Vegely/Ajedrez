

#include "Tablero.h"
#include <iostream>
#include "graphics.h"

int main(int argc, char* argv[])
{
	Tablero tablero; //Creación del tablero con las piezas

	init(&argc, argv, "Ajedrez", 1280, 720);
	//TEST UNITARIO PARA VER SI MUEVEN Y COMEN LAS PIEZAS
	////////////////////////////////////////////////////////////
	tablero.mover(Posicion{ 1,0 }, Posicion{ 2,2 });
	tablero.mover(Posicion{ 1,6 }, Posicion{ 1,4 });
	tablero.mover(Posicion{ 2,2 }, Posicion{ 1,4 });
	tablero.mover(Posicion{ 2,2 }, Posicion{ 1,4 });
	tablero.mover(Posicion{ 1,4 }, Posicion{ 2,6 });
	tablero.imprimeTablero();
	////////////////////////////////////////////////////////////
	
	std::cout << "sopdjasopk";

	return 0;
}