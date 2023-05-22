#include "Torre.h"

#include "Tablero.h"

DatosClavada Torre::actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8])
{
	clearVariables();
	DatosClavada piezaClavada;
	Posicion posicionAux;
	bool piezaEncontrada = false; //Variable para comprobar si se ha topado con una pieza

	if (!clavada)
	{
		Posicion direcciones[] = { Posicion(-1, 0), Posicion(1, 0), Posicion(0, -1), Posicion(0, 1) };		//Direcciones paralelas
		for (Posicion direccion : direcciones)
		{
			Posicion posicion_prueba = posicion + direccion;
			piezaEncontrada = false;
			while (posicion_prueba >= Posicion(0, 0) && posicion_prueba < Posicion(8, 8))		//Comprueba si la posicion se encuentra dentro del tablero
			{
				if (!piezaEncontrada)
				{
					if (tablero.leer(posicion_prueba) == nullptr)		//La casilla revisada est� vac�a
					{
						puede_mover.push_back(posicion_prueba);			//A�ade los vacios de la linea a puede_mover
						tableroIlegalesRey[(color + 1) % 2][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
						posicion_prueba += direccion;					//Actualiza la siguiente posici�n
					}
					else if (tablero.leer(posicion_prueba)->color != color)		//La casilla revisada tiene una pieza enemiga
					{
						puede_comer.push_back(tablero.leer(posicion_prueba));		//A�ade la pieza enemiga a puede_comer
						tablero.leer(posicion_prueba)->addAmenazas(this);		//Se a�ade a las amenazas de la otra pieza
						piezaEncontrada = true;
						posicionAux = posicion_prueba;
					}
					else		//La casilla revisada tiene una pieza amiga
					{
						tablero.leer(posicion_prueba)->addProtecciones(this);		//Añade la pieza amiga a esta_protegiendo
						tableroIlegalesRey[(color + 1) % 2][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
						break;
					}
				}
				else
				{
					if (tablero.leer(posicion_prueba) != nullptr)
					{
						if (tablero.leer(posicion_prueba)->tipo == Pieza::tipo_t::REY)		//La casilla revisada tiene un rey
						{
							piezaClavada.ExisteClavada = true;
							piezaClavada.DireccionClavada = direccion;
							piezaClavada.PiezaClavada = tablero.leer(posicion_prueba);
							break;
						}
						else		//La casilla revisada tiene una pieza amiga
						{
							break;
						}
					}
				}
			}
		}
	}
	else
	{
		Posicion direcciones[] = { direccionClavada,-direccionClavada };
		for (Posicion direccion : direcciones)
		{
			Posicion posicion_prueba = posicion + direccion;
			piezaEncontrada = false;
			while (posicion_prueba >= Posicion(0, 0) && posicion_prueba < Posicion(8, 8))		//Comprueba si la posicion se encuentra dentro del tablero
			{
				if (!piezaEncontrada)
				{
					if (tablero.leer(posicion_prueba) == nullptr)		//La casilla revisada est� vac�a
					{
						puede_mover.push_back(posicion_prueba);			//A�ade los vacios de la linea a puede_mover
						tableroIlegalesRey[(color + 1) % 2][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
						posicion_prueba += direccion;					//Actualiza la siguiente posici�n
					}
					else if (tablero.leer(posicion_prueba)->color != color)		//La casilla revisada tiene una pieza enemiga
					{
						puede_comer.push_back(tablero.leer(posicion_prueba));		//A�ade la pieza enemiga a puede_comer
						tablero.leer(posicion_prueba)->addAmenazas(this);		//Se a�ade a las amenazas de la otra pieza
						piezaEncontrada = true;
						posicionAux = posicion_prueba;
					}
					else		//La casilla revisada tiene una pieza amiga
					{
						tablero.leer(posicion_prueba)->addProtecciones(this);		//Añade la pieza amiga a esta_protegiendo
						tableroIlegalesRey[(color + 1) % 2][posicion_prueba.x][posicion_prueba.y] = true; //Asignar como posible amenaza para el rey rival, por eso se cambia el color
						break;
					}
				}
				else
				{
					if (tablero.leer(posicion_prueba) != nullptr)
					{
						if (tablero.leer(posicion_prueba)->tipo == Pieza::tipo_t::REY)		//La casilla revisada tiene un rey
						{
							piezaClavada.ExisteClavada = true;
							piezaClavada.DireccionClavada = direccion;
							piezaClavada.PiezaClavada = tablero.leer(posicion_prueba);
							break;
						}
						else		//La casilla revisada tiene una pieza amiga
						{
							break;
						}
					}
				}
			}
		}
	}
	return piezaClavada;
}