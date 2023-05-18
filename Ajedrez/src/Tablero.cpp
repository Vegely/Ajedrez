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

Tablero::Tablero(const Tablero& tablero)
{
	for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++)
	{
		if (tablero.tablero != nullptr)
		{
			switch (tablero.tablero[i]->tipo)
			{
			case Pieza::tipo_t::PEON:
				escribir(tablero.posicion(i), new Peon(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::CABALLO:
				escribir(tablero.posicion(i), new Caballo(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::ALFIL:
				escribir(tablero.posicion(i), new Alfil(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::TORRE:
				escribir(tablero.posicion(i), new Torre(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::DAMA:
				escribir(tablero.posicion(i), new Dama(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::REY:
				escribir(tablero.posicion(i), new Rey(*this, tablero.tablero[i]->color));
				break;
			}
		}
		else this->tablero[i] = nullptr;
	}
}

Tablero::~Tablero()
{
	for (Pieza* p_pieza : tablero) delete p_pieza;
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
	
	// Pintar el tablero
	int i = 0;
	for (Pieza* p_pieza : tablero)
	{
		if (p_pieza == nullptr) std::cout << "---\t";
		else std::cout << p_pieza->getNombre() << " " << p_pieza->color << "\t";

		if (i++ % 8 == 7) std::cout << "\n\n";
	}
}

void Tablero::actualizarTablero() 
{
	for (Pieza* p_pieza : tablero) if(p_pieza != nullptr) p_pieza->actualizarVariables();
}

bool Tablero::mover(const Movimiento& movimiento) {
	if (leer(movimiento.inicio) == nullptr)		//Si no hay pieza en p1 no se puede mover
	{
		return false;
	}
	else
	{
		if (leer(movimiento.fin) == nullptr)	//Si no hay pieza en p2 si se puede mover se mueve
		{
			for (const Posicion puedeMover : leer(movimiento.inicio)->getPuedeMover())
			{
				if (puedeMover == movimiento.fin)
				{
					tablero[movimiento.fin.x + movimiento.fin.y * ANCHO_TABLERO] = leer(movimiento.inicio);
					leer(movimiento.fin)->posicion = movimiento.fin;
					tablero[movimiento.inicio.x + movimiento.inicio.y * ANCHO_TABLERO] = nullptr;
					actualizarTablero();
					return true;
				}
			}
			return false;			//Si no se ha podido porque no es posible
		}
		else
		{
			for (const Pieza* puedeComer:leer(movimiento.inicio)->getPuedeComer())
			{
				if (puedeComer == leer(movimiento.fin))
				{
					borrar(movimiento.fin); //Liberar espacio de memoria de la pieza comida
					tablero[movimiento.fin.x + movimiento.fin.y * ANCHO_TABLERO] = leer(movimiento.inicio);
					leer(movimiento.fin)->posicion = movimiento.fin;
					tablero[movimiento.inicio.x + movimiento.inicio.y * ANCHO_TABLERO] = nullptr;
					actualizarTablero();
					return true;
				}
			}
			return false; //Si no se ha podido porque no es posible
		}
	}
}