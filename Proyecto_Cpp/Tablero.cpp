#include "Tablero.h"

#include "Caballo.h"
#include "Rey.h"
#include "Peon.h"
#include "Alfil.h"
#include "Torre.h"
#include "Reina.h"
#include <iostream>
#include <string>

Tablero::Tablero()
{
	for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++) { tablero[i] = nullptr; } //Se crea un tablero vacio

	//True == Blancas <-> False == Negras En color
	//Blancas 
	//Se añaden los peones
	for (int i = 0; i < ANCHO_TABLERO; i++)
	{
		escribir(Posicion(i, 1), new Peon(*this, true));
	}
	//Se añaden las torres
	escribir(Posicion(0, 0), new Torre(*this, true));
	escribir(Posicion(7, 0), new Torre(*this, true));

	//Se escriben los caballos
	escribir(Posicion(1, 0), new Caballo(*this, true));
	escribir(Posicion(6, 0), new Caballo(*this, true));

	//Se escriben los alfiles
	escribir(Posicion(2, 0), new Alfil(*this, true));
	escribir(Posicion(5, 0), new Alfil(*this, true));

	//Se escribe la dama y el rey
	escribir(Posicion(3, 0), new Reina(*this, true));
	escribir(Posicion(4, 0), new Rey(*this, true));

	//Negras
	//Se añaden los peones
	for (int i = 0; i < ANCHO_TABLERO; i++)
	{
		escribir(Posicion(i, 6), new Peon(*this, false));
	}
	//Se añaden las torres
	escribir(Posicion(0, 7), new Torre(*this, false));
	escribir(Posicion(7, 7), new Torre(*this, false));

	//Se escriben los caballos
	escribir(Posicion(1, 7), new Caballo(*this, false));
	escribir(Posicion(6, 7), new Caballo(*this, false));

	//Se escriben los alfiles
	escribir(Posicion(2, 7), new Alfil(*this, false));
	escribir(Posicion(5, 7), new Alfil(*this, false));

	//Se escribe la dama y el rey
	escribir(Posicion(3, 7), new Reina(*this, false));
	escribir(Posicion(4, 7), new Rey(*this, false));

}

void Tablero::escribir(const Posicion& posicion, Pieza* pieza)
{
	tablero[posicion.x + posicion.y * ANCHO_TABLERO] = pieza;
	pieza->posicion = posicion;
}

void Tablero::borrar(const Posicion& posicion)
{
	if (leer(posicion) != nullptr)
	{
		delete tablero[posicion.x + posicion.y * ANCHO_TABLERO];
		tablero[posicion.x + posicion.y * ANCHO_TABLERO] = nullptr;
	}
}



void Tablero::imprimeTablero() {
	for (int i = 0; i < 40; i++) {
		std::cout << std::endl << std::endl;
	}
	
	for (int i = 0; i < ANCHO_TABLERO ; i++)
	{	
		for (int j = 0; j < ANCHO_TABLERO; j++)
		{	
			if (leer(Posicion{ (char)j,(char)i })!=nullptr)
			{
				std::cout << leer(Posicion{ (char)j,(char)i })->nombre <<" " << leer(Posicion{(char)j,(char)i})->color << "	";
			}
			else
			{
				std::cout << "  ▄		";
			}
			
		}
		std::cout << std::endl << std::endl;
	}
}

void Tablero::actualizarTablero() {
	for (int i = 0; i < ANCHO_TABLERO; i++)
	{
		for (int j = 0; j < ANCHO_TABLERO; j++)
		{
			if (leer(Posicion{ (char)i,(char)j }) != nullptr)
			{
				 leer(Posicion{ (char)i,(char)j })->actualizarVariables();
			}
		}
	}
}

bool Tablero::mover(const Posicion& p1, const Posicion& p2) {
	if (leer(p1) == nullptr)
	{
		return false;
	}
	else
	{
		if (leer(p2) == nullptr)
		{
			for (const Posicion puedeMover : leer(p1)->getPuedeMover())
			{
				
				if (puedeMover == p2)
				{
					auto& aux = *leer(p1);
					tablero[p2.x + p2.y * ANCHO_TABLERO] = new Pieza(aux);
					borrar(p1);
					return true;
				}
				//else
				//{
				//	return false;
				//}
			}
		}
		else
		{
			return false;
		}
	}
}