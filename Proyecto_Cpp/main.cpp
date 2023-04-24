#include "Tablero.h"

#include <iostream>

using namespace std;

int main()
{
	Tablero tablero;
	tablero.leer(Posicion(3, 2))->mover();

	for (const Posicion puedeMover : tablero.leer(Posicion(3, 2))->getPuedeMover())
	{
		cout << (int)puedeMover.x << " " << (int)puedeMover.y << endl;
	}

	return 0;
}