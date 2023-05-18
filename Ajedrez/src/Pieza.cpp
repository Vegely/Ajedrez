#include "Pieza.h"
#include "Tablero.h"


void Pieza::clearVariables()
{
	puede_mover.clear();
	puede_comer.clear();
	esta_protegida.clear();
	amenazas.clear();
}


void Pieza::mover()
{
	actualizarVariables();
}


