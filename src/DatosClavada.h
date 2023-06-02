#pragma once
#include <vector>
#include "Posicion.h"

class Pieza;

struct DatosClavada
{
	bool ExisteClavada=false;
	Posicion DireccionClavada = Posicion{ -1, -1 };
	Pieza* PiezaClavada = nullptr;
};

