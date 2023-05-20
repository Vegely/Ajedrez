#include "Alfil.h"

#include "Tablero.h"

void Alfil::actualizarVariables()
{
	clearVariables();

	Posicion direcciones[] = { Posicion(-1, -1), Posicion(1, -1), Posicion(-1, 1), Posicion(1, 1) };		//Direcciones diagonales

	for (Posicion direccion : direcciones)
	{
		Posicion posicion_prueba = posicion + direccion;
		while (posicion_prueba >= Posicion(0, 0) && posicion_prueba < Posicion(8, 8))		//Comprueba si la posicion se encuentra dentro del tablero
		{
			if (tablero.leer(posicion_prueba) == nullptr)		//La casilla revisada está vacía
			{
				puede_mover.push_back(posicion_prueba);			//Añade los vacios de la linea a puede_mover
				posicion_prueba += direccion;					//Actualiza la siguiente posición
			}
			else if (tablero.leer(posicion_prueba)->color != color)		//La casilla revisada tiene una pieza enemiga
			{
				puede_comer.push_back(tablero.leer(posicion_prueba));		//Añade la pieza enemiga a puede_comer
				tablero.leer(posicion_prueba)->addAmenazas(this);		//Se añade a las amenazas de la otra pieza
				break;
			}
			else		//La casilla revisada tiene una pieza amiga
			{
				tablero.leer(posicion_prueba)->addProtecciones(this);		//Añade la pieza amiga a esta_protegiendo
				break;
			}
		}
	}
}