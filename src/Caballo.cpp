#include "Caballo.h"
#include "Tablero.h"


DatosClavada Caballo::actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) {
	clearVariables();
	

	DatosClavada piezaClavada;

	if (clavada) //Si el caballo esta clavado no puede mover
		return piezaClavada;

	Posicion direcciones[] = {  Posicion(-2, 1), Posicion(-2, -1),		//Direcciones izquierda
								Posicion(-1, -2), Posicion(1,-2),		//Direcciones abajo
								Posicion(2, -1), Posicion(2, 1),		//Direcciones derecha
								Posicion(1, 2), Posicion(-1, 2) };		//Direcciones arriba

	for (Posicion direccion : direcciones) {
		Posicion posicion_prueba = posicion + direccion;
		if (posicion_prueba >= Posicion(0, 0) && posicion_prueba < Posicion(8, 8))		//Comprueba si la posicion se encuentra dentro del tablero
		{
			if (tablero.leer(posicion_prueba) == nullptr)		//La casilla revisada está vacía
			{
				puede_mover.push_back(posicion_prueba);			//Añade los vacios de la linea a puede_mover
				tableroIlegalesRey[!color][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
			}
			else if (tablero.leer(posicion_prueba)->color != color)		//La casilla revisada tiene una pieza enemiga
			{
				puede_comer.push_back(tablero.leer(posicion_prueba));		//Añade la pieza enemiga a puede_comer
				tablero.leer(posicion_prueba)->addAmenazas(this);		//Se añade a las amenazas de la otra pieza
			}
			else		//La casilla revisada tiene una pieza amiga
			{
				tablero.leer(posicion_prueba)->addProtecciones(this);		//Añade la pieza amiga a esta_protegiendo
				tableroIlegalesRey[!color][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
			}
		}
	}
	return piezaClavada;
}
