#include "Peon.h"
#include "Tablero.h"


void Peon::actualizarVariables() {
	clearVariables();

	if (color) {
		Posicion direcciones[] = { Posicion(0, 1),						//Direccion	  mover
								Posicion(-1, 1), Posicion(1,1) };		//Direcciones Comer

		for (Posicion direccion : direcciones) {
			Posicion posicion_prueba = posicion + direccion;
			if (posicion_prueba >= Posicion(0, 0) && posicion_prueba < Posicion(8, 8))		//Comprueba si la posicion se encuentra dentro del tablero
			{
				if (direccion == Posicion{ 0, 1 }&& tablero.leer(posicion_prueba) == nullptr)
				{

					puede_mover.push_back(posicion_prueba);			//Añade los vacios de la linea a puede_mover
					posicion_prueba += Posicion{ 0,1 };
					if (posicion.y == 1 && tablero.leer(posicion_prueba ) == nullptr) //Si esta en la casilla inicial puede mover 2
					{
						puede_mover.push_back(posicion_prueba );
					}
				}
				else
				{
					if (tablero.leer(posicion_prueba) != nullptr && direccion != direcciones[0]) //Para que no de error de atributos no inicializados
					{
						if (tablero.leer(posicion_prueba)->color != color)		//La casilla revisada tiene una pieza enemiga
						{
							puede_comer.push_back(tablero.leer(posicion_prueba));		//Añade la pieza enemiga a puede_comer
							tablero.leer(posicion_prueba)->addAmenazas(this);		//Se añade a las amenazas de la otra pieza
						}
						else		//La casilla revisada tiene una pieza amiga
						{
							esta_protegiendo.push_back(tablero.leer(posicion_prueba));		//Añade la pieza amiga a esta_protegiendo
						}

					}

				}
			}
		}
	}
	else {
		Posicion direcciones[] = { Posicion(0, -1),						//Direccion	  mover
								Posicion(-1, -1), Posicion(1,-1) };		//Direcciones Comer

		for (Posicion direccion : direcciones) {
			Posicion posicion_prueba = posicion + direccion;
			if (posicion_prueba >= Posicion(0, 0) && posicion_prueba < Posicion(8, 8))		//Comprueba si la posicion se encuentra dentro del tablero
			{
				if (direccion == Posicion{ 0, -1 } && tablero.leer(posicion_prueba) == nullptr)
				{
					puede_mover.push_back(posicion_prueba);			//Añade los vacios de la linea a puede_mover
					posicion_prueba += Posicion{ 0,-1 };
					if (posicion.y == 7 && tablero.leer(posicion_prueba ) == nullptr) //Si esta en la casilla inicial puede mover 2
					{
						puede_mover.push_back(posicion_prueba);
					}

				}
				else
				{
					if (tablero.leer(posicion_prueba) != nullptr && direccion != direcciones[0]) //Para que no de error de atributos no inicializados
					{
						if (tablero.leer(posicion_prueba)->color != color)		//La casilla revisada tiene una pieza enemiga
						{
							puede_comer.push_back(tablero.leer(posicion_prueba));	//Añade la pieza enemiga a puede_comer
							tablero.leer(posicion_prueba)->addAmenazas(this);		//Se añade a las amenazas de la otra pieza
						}
						else		//La casilla revisada tiene una pieza amiga
						{
							esta_protegiendo.push_back(tablero.leer(posicion_prueba));		//Añade la pieza amiga a esta_protegiendo
						}
					}
				}
			}
		}
	}
}