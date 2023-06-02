#include "InfoTablas.h"

#include "Tablero.h"

void InfoTablas::add(const Tablero& tablero)
{
	bool encontrado = false;
	for (int i = 0; i < posiciones.size(); i++)
	{
		int j = 0;
		for (int k = 0; k < ANCHO_TABLERO * ANCHO_TABLERO; k++)
		{
			if (posiciones[i].tablero[k] == tablero.tablero[k]) j++;
		}
		if (j == ANCHO_TABLERO * ANCHO_TABLERO)
		{
			if(++repeticiones[i] == 3) boolRepeticion = true;
			encontrado = true;
			break;
		}
	}
	
	Tablero aux = tablero;

	if (!encontrado)
	{
		posiciones.push_back(aux);
		repeticiones.push_back(1);
	}
	contadorJugadas++;
}