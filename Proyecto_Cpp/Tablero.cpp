#include "Tablero.h"

#include "Alfil.h"
#include "Torre.h"
#include "Reina.h"

Tablero::Tablero()
{
	for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++) { tablero[i] = nullptr; }

	//Se añaden dos torres abitrarias
	escribir(Posicion(3, 2), new Reina(*this, false));
	escribir(Posicion(4, 3), new Torre(*this, true));
}

void Tablero::escribir(const Posicion& posicion, Pieza* pieza)
{
	tablero[posicion.x + posicion.y * ANCHO_TABLERO] = pieza;
	pieza->posicion = posicion;
}