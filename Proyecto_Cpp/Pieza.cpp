#include "Pieza.h"

void Pieza::clearVariables()
{
	puede_mover.clear();
	puede_comer.clear();
	esta_protegiendo.clear();
	amenazas.clear();
}

void Pieza::mover()
{
	actualizarVariables();
}