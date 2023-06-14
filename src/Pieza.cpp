#include "Pieza.h"
#include "Tablero.h"

void Pieza::clearVariables()
{
	puede_mover.clear();
	puede_comer.clear();
}

Pieza& Pieza::operator=(const Pieza& rhs)
{
	puede_mover = rhs.puede_mover;

	for (Pieza* p_pieza : rhs.puede_comer) puede_comer.push_back(rhs.tablero.leer(p_pieza->posicion));
	for (Pieza* p_pieza : rhs.esta_protegida) esta_protegida.push_back(rhs.tablero.leer(p_pieza->posicion));
	for (Pieza* p_pieza : rhs.amenazas) amenazas.push_back(rhs.tablero.leer(p_pieza->posicion));

	return *this;
}