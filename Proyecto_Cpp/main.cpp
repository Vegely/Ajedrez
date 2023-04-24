#include "Tablero.h"

#include <iostream>

using namespace std;

int main()
{
	Tablero tablero;
	Posicion p{ 3, 4 };

	tablero.leer(p)->mover();

	for (const Posicion puedeMover : tablero.leer(p)->getPuedeMover())
	{
		cout << (int)puedeMover.x << " " << (int)puedeMover.y << endl;
	}

	return 0;
}