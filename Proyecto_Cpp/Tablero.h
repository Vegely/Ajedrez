#ifndef _TABLERO__H_
#define	_TABLERO__H_


#include "Pieza.h"

#define ANCHO_TABLERO 8

class Tablero
{
	Pieza* tablero[ANCHO_TABLERO * ANCHO_TABLERO];

	void clearVariablesDePiezas() { for (Pieza* p_pieza : tablero) p_pieza->clearVariables(); }

	void escribir(const Posicion& posicion, Pieza* pieza);

public:
	explicit Tablero();
	inline Pieza* leer(const Posicion& posicion) const { return tablero[posicion.x + posicion.y * ANCHO_TABLERO]; }
	void imprimeTablero();
};


#endif