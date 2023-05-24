#include "Peon.h"
#include "Tablero.h"

constexpr int Y[2] = {6,1};

DatosClavada Peon::actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) {
	clearVariables();
	DatosClavada piezaClavada;

	int YInicio;
	std::vector<Posicion> direcciones;
	

	YInicio = Y[color];


	if (color) { //Comprueba si el peon es blanco por asignar una direccionalidad de movimiento u otra.
		direcciones = {Posicion(0, 1),						//Direccion	  mover
								Posicion(-1, 1), Posicion(1,1) };		//Direcciones Comer
		if (clavada) {
			bool SPBN = true;
			for (auto movDirec : direcciones)
			{
				if (movDirec == direccionClavada || movDirec == -direccionClavada)
				{
					direcciones = {movDirec};
					SPBN = false;
				}
			}
			if(!SPBN)
				return piezaClavada;
		}
	

	}
	else
	{
		direcciones = { Posicion(0, -1),						//Direccion	  mover
								Posicion(-1, -1), Posicion(1,-1) };		//Direcciones Comer
		if (clavada) {
			bool SPBN = true;
			for (auto movDirec : direcciones)
			{
				if (movDirec == direccionClavada || movDirec == -direccionClavada)
				{
					direcciones = { movDirec };
					SPBN = false;
				}
			}
			if (!SPBN) //Si no puede mover en ninguna dirección esta clavado
				return piezaClavada;
		}

	}
		
	for (Posicion direccion : direcciones) {
		Posicion posicion_prueba = posicion + direccion;
		if (posicion_prueba >= Posicion(0, 0) && posicion_prueba < Posicion(8, 8))		//Comprueba si la posicion se encuentra dentro del tablero
		{
			if (direccion == direcciones[0] && tablero.leer(posicion_prueba) == nullptr)
			{
				puede_mover.push_back(posicion_prueba);			//Añade los vacios de la linea a puede_mover
				tableroIlegalesRey[!color][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
				posicion_prueba += direcciones[0];
				if (posicion.y == YInicio && tablero.leer(posicion_prueba ) == nullptr) //Si esta en la casilla inicial puede mover 2
				{
					puede_mover.push_back(posicion_prueba );
					tableroIlegalesRey[!color][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
				}
			}
			else
			{
				tableroIlegalesRey[!color][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
				if (tablero.leer(posicion_prueba) != nullptr && direccion != direcciones[0]) //Para que no de error de atributos no inicializados
				{
					if (tablero.leer(posicion_prueba)->color != color)		//La casilla revisada tiene una pieza enemiga
					{
						puede_comer.push_back(tablero.leer(posicion_prueba));		//Añade la pieza enemiga a puede_comer
						tablero.leer(posicion_prueba)->addAmenazas(this);		//Se añade a las amenazas de la otra pieza
					}
					else	//La casilla revisada tiene una pieza amiga
					{
						tablero.leer(posicion_prueba)->addProtecciones(this);		//Añade la pieza amiga a esta_protegiendo
					}

				}

			}
		}
	}
	
	return piezaClavada;
}