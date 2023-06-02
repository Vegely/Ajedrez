#include "Rey.h"
#include "Tablero.h"


//El rey no puede clavarse
DatosClavada Rey::actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) {
	clearVariables();
	DatosClavada piezaClavada;

	Posicion direcciones[] = { Posicion(-1, 0), Posicion(1, 0), Posicion(0, -1), Posicion(0, 1),		//Direcciones paralelas
								Posicion(-1, -1), Posicion(1, -1), Posicion(-1, 1), Posicion(1, 1) };		//Direcciones diagonales

	for (Posicion direccion : direcciones) {
		Posicion posicion_prueba = posicion + direccion;
		
		if (posicion_prueba >= Posicion(0, 0) && posicion_prueba < Posicion(8, 8) )		//Comprueba si la posicion se encuentra dentro del tablero
		{
			tableroIlegalesRey[!color][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
			if (tableroIlegalesRey[color][posicion_prueba.x][posicion_prueba.y] == false)
			{
				if (tablero.leer(posicion_prueba) == nullptr)		//La casilla revisada está vacía
				{
					puede_mover.push_back(posicion_prueba);			//Añade los vacios de la linea a puede_mover
				}
				else if (tablero.leer(posicion_prueba)->color != color)		//La casilla revisada tiene una pieza enemiga
				{
					puede_comer.push_back(tablero.leer(posicion_prueba));		//Añade la pieza enemiga a puede_comer
					tablero.leer(posicion_prueba)->addAmenazas(this);		//Se añade a las amenazas de la otra pieza
				}
				else		//La casilla revisada tiene una pieza amiga
				{
					tablero.leer(posicion_prueba)->addProtecciones(this);		//Añade la pieza amiga a esta_protegiendo
				}
			}
		}
	}
	
	return piezaClavada;
}
