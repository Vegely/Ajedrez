#include "Tablero.h"

#include "Caballo.h"
#include "Rey.h"
#include "Peon.h"
#include "Alfil.h"
#include "Torre.h"
#include "Dama.h"
#include <iostream>
#include <string>

constexpr auto NUM_LINEAS = 40;

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
	escribir(Posicion(3, 0), new Dama(*this, true));
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
	escribir(Posicion(3, 7), new Dama(*this, false));
	escribir(Posicion(4, 7), new Rey(*this, false));

	actualizarTablero(); //Se inicializan los movimientos posibles
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
		delete tablero[posicion.x + posicion.y * ANCHO_TABLERO];		//Se libera el puntero
		tablero[posicion.x + posicion.y * ANCHO_TABLERO] = nullptr;		//Se asigna a NULL
	}
}



void Tablero::imprimeTablero() {
	//Insertar lineas vacias para limpiar consola
	for (int i = 0; i < NUM_LINEAS; i++) {
		std::cout << std::endl << std::endl;
	}
	
	for (int i = 0; i < ANCHO_TABLERO ; i++)
	{	
		for (int j = 0; j < ANCHO_TABLERO; j++)
		{	
			if (leer(Posicion{ (char)j,(char)i })!=nullptr) //Si == nullptr no hay pieza
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
			if (leer(Posicion{ (char)i,(char)j }) != nullptr) //Si == nullptr no hay pieza
			{
				 leer(Posicion{ (char)i,(char)j })->actualizarVariables();
			}
		}
	}
}

bool Tablero::mover(const Posicion& p1, const Posicion& p2) {
	if (leer(p1) == nullptr)		//Si no hay pieza en p1 no se puede mover
	{
		return false;
	}
	else
	{
		if (leer(p2) == nullptr)	//Si no hay pieza en p2 si se puede mover se mueve
		{
			for (const Posicion puedeMover : leer(p1)->getPuedeMover())
			{
				if (puedeMover == p2)
				{
					tablero[p2.x + p2.y * ANCHO_TABLERO] = leer(p1);
					leer(p2)->posicion = p2;
					tablero[p1.x + p1.y * ANCHO_TABLERO] = nullptr;
					actualizarTablero();
					return true;
				}
			}
			return false;			//Si no se ha podido porque no es posible
		}
		else
		{
			for (const Pieza* puedeComer:leer(p1)->getPuedeComer())
			{
				if (puedeComer == leer(p2))
				{
					borrar(p2); //Liberar espacio de memoria de la pieza comida
					tablero[p2.x + p2.y * ANCHO_TABLERO] = leer(p1);
					leer(p2)->posicion = p2;
					tablero[p1.x + p1.y * ANCHO_TABLERO] = nullptr;
					actualizarTablero();
					return true;
				}
			}
			return false; //Si no se ha podido porque no es posible
		}
	}
}