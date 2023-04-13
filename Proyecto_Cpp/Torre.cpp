#include "Torre.h"

#include "Tablero.h"

void Torre::actualizarVariables()
{
	Posicion direcciones[] = { Posicion(-1, 0), Posicion(1, 0), Posicion(0, -1), Posicion(0, 1) };		//Direcciones paralelas

	for (Posicion direccion : direcciones)
	{
		Posicion posicion_pruba = posicion + direccion;
		while (posicion_pruba >= Posicion(0, 0) && posicion_pruba < Posicion(8, 8))		//Comprueba si la posicion se encuentra dentro del tablero
		{
			if (tablero.leer(posicion_pruba) == nullptr)		//La casilla revisada está vacía
			{
				puede_mover.push_back(posicion_pruba);			//Añade los vacios de la linea a puede_mover
				posicion_pruba += direccion;					//Actualiza la siguiente posición
			}
			else if (tablero.leer(posicion_pruba)->color != color)		//La casilla revisada tiene una pieza enemiga
			{
				puede_comer.push_back(tablero.leer(posicion_pruba));		//Añade la pieza enemiga a puede_comer
				tablero.leer(posicion_pruba)->addAmenazas(this);		//Se añade a las amenazas de la otra pieza
				break;
			}
			else		//La casilla revisada tiene una pieza amiga
			{
				esta_protegiendo.push_back(tablero.leer(posicion_pruba));		//Añade la pieza amiga a esta_protegiendo
				break;
			}
		}
	}
}