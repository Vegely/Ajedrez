#ifndef _CAJA__H_
#define _CAJA__H_

#include "Punto.h"

#define ULY 25.0f
#define ULX -31.5f
#define DRY -10.0f
#define DRX 31.5f

class Caja
{
public:
	Caja(float ulx, float uly, float drx, float dry);
	bool enCaja(float x, float y);
	void dibuja();
	Punto ul;
	Punto dr;
};

#endif