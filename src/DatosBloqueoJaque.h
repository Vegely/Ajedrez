#ifndef _DATOSBLOQUEOJAQUE__H_
#define _DATOSBLOQUEOJAQUE__H_
#include "pieza.h"

struct DatosBloqueoJaque
{
	Pieza* datosPieza=nullptr;
	Posicion posicionPieza = Posicion{ 0,0 };
};

#endif