#ifndef _DATOSCLAVADA__H_
#define _DATOSCLAVADA__H_

#include <vector>
#include "Posicion.h"

class Pieza;

struct DatosClavada
{
	bool ExisteClavada=false;
	Posicion DireccionClavada = Posicion{ -1, -1 };
	Pieza* PiezaClavada = nullptr;
};

#endif