#include "Tablero.h"
#include "Callbacks.h"
#include <iostream>



int main(int argc, char* argv[])
{
	Tablero tablero; //Creación del tablero con las piezas
	graphicsInit(&argc, argv); // Inicialización del motor gráfico

	//init(&argc, argv, "Ajedrez", 1280, 720);
	//TEST UNITARIO PARA VER SI MUEVEN Y COMEN LAS PIEZAS
	////////////////////////////////////////////////////////////
	/* Desilenciar	
	tablero.imprimeTablero();
	std::cin.get();
	tablero.mover(Movimiento(Posicion{ 1,0 }, Posicion{ 2,2 }));
	tablero.imprimeTablero();
	std::cin.get();
	tablero.mover(Movimiento(Posicion{ 1,6 }, Posicion{ 1,4 }));
	tablero.imprimeTablero();
	std::cin.get();
	tablero.mover(Movimiento(Posicion{ 2,2 }, Posicion{ 1,4 }));
	tablero.imprimeTablero();
	std::cin.get();
	tablero.mover(Movimiento(Posicion{ 2,2 }, Posicion{ 1,4 }));
	tablero.imprimeTablero();
	std::cin.get();
	tablero.mover(Movimiento(Posicion{ 1,4 }, Posicion{ 2,6 }));
	tablero.imprimeTablero();
	////////////////////////////////////////////////////////////
	
	std::cout << "1";
	*/

	return 0;
}