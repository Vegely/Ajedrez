#include "MotorDeJuego.h"

#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Torre.h"
#include "Rey.h"
#include "Dama.h"

constexpr auto NUM_LINEAS = 40;

////////////////////////

#include <iostream>
#include <windows.h>

void MotorDeJuego::pintar(Posicion posSelec) const
{
	//Insertar lineas vacias para limpiar consola
	for (int i = 0; i < NUM_LINEAS; i++) {
		std::cout<< std::endl;
	}

	// Pintar el tablero
	int i = 0, j = 1;
	for (int x = 0; x < ANCHO_TABLERO * ANCHO_TABLERO; x++)
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

		if (i % 8 == 0) std::cout << "    " << j++ << "\t"; // Pintar los numeros

		if (posSelec != Posicion(-1, -1)) // Seleccionar el color de fondo
		{
			if (Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == posSelec) SetConsoleTextAttribute(hStdout, 160);
			else
			{
				for (Posicion puedeMover : tablero.leer(posSelec)->getPuedeMover()) if (Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == puedeMover)
				{
					if (tablero.leer(posSelec)->getTipo() != Pieza::tipo_t::PEON || (puedeMover - tablero.leer(posSelec)->getPosicion()).x == 0)
					{
						SetConsoleTextAttribute(hStdout, 176);
					}
					else
					{
						SetConsoleTextAttribute(hStdout, 64);
					}
				}
					
				for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer()) if (Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == puedeComer->getPosicion())
				{
						SetConsoleTextAttribute(hStdout, 64);
				}
					
			}
				
		}
		
		if (tablero.tablero[x] == nullptr) std::cout << "---\t";
		else std::cout << tablero.tablero[x]->getNombre() << " " << tablero.tablero[x]->getColor() << "\t";

		SetConsoleTextAttribute(hStdout, 7);

		if (i++ % 8 == 7) std::cout << "\n\n";
	}

	std::cout << "\t";
	for (char i = 'A'; i <= 'H'; i++) std::cout << " " << i << " \t"; // Pintar las letras
	std::cout << std::endl;
}

////////////////////////

bool MotorDeJuego::hacerJugada(Movimiento movimiento)
{
	bool JugadaHecha = false;

	for (const Posicion puedeMover : tablero.leer(movimiento.inicio)->getPuedeMover())
	{
		if (puedeMover == movimiento.fin)
		{ 
			if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::REY)
			{
				Posicion aux = movimiento.fin - movimiento.inicio;
				if (abs(aux.x) == 2)
				{
					if (aux.x < 0) tablero.mover(Movimiento(Posicion(0, movimiento.inicio.y), Posicion(3, movimiento.inicio.y)));
					else tablero.mover(Movimiento(Posicion(7, movimiento.inicio.y), Posicion(5, movimiento.inicio.y)));

					tablero.infoTablas.clear();
				}	
			}

			

			tablero.actualizarHaMovido(movimiento);
			/*
			if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON && (puedeMover - tablero.leer(movimiento.inicio)->getPosicion()).x != 0)
			{
				Posicion desplazamientoBorrado = Posicion{ 0,(int)pow(-1,tablero.leer(movimiento.inicio)->getColor()) };
				delete tablero.leer(movimiento.fin+desplazamientoBorrado);
			}
			*/
			JugadaHecha = true; 
			break; 
		}
	}
		
	if (!JugadaHecha) for (const Pieza* puedeComer : tablero.leer(movimiento.inicio)->getPuedeComer())
	{
		if (puedeComer->getPosicion() == movimiento.fin && tablero.leer(movimiento.fin) != nullptr)
		{
			tablero.actualizarHaMovido(movimiento);

			delete tablero.leer(movimiento.fin);

			tablero.infoTablas.clear();
			tablero.numeroPiezas--;

			JugadaHecha = true;
			break;
		}

		/*
		if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON )
		{
			Posicion desplazamientoBorrado = Posicion{ 0,(int)pow(-1,tablero.leer(movimiento.inicio)->getColor()) };
			if (puedeComer->getPosicion() == movimiento.fin+ desplazamientoBorrado && tablero.leer(movimiento.fin+ desplazamientoBorrado) != nullptr)
			{
				delete tablero.leer(movimiento.fin + desplazamientoBorrado);
				JugadaHecha = true;
				break;
			}
			
		}*/

	}
		

	if (JugadaHecha)
	{
		if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON && movimiento.fin.y % 7 == 0)
			coronar(movimiento.inicio);

		tablero.cambiarTurno();
		tablero.ultimaJugada = movimiento;
		tablero.mover(movimiento);
		
		pintar();

		return true;
	}

	return false;
}

/////////////////

#include <string>

Pieza::tipo_t getSelection()
{
	std::string input;
	Pieza::tipo_t tipo;

	bool exit = false;
	while (!exit)
	{
		exit = true;
		
		std::cin >> input;
		int numero = input[0] - 48;
		switch (numero)
		{
		case 1:
			tipo = Pieza::tipo_t::CABALLO;
			break;
		case 2:
			tipo = Pieza::tipo_t::ALFIL;
			break;
		case 3:
			tipo = Pieza::tipo_t::TORRE;
			break;
		case 4:
			tipo = Pieza::tipo_t::DAMA;
			break;
		default:
			exit = false;
		}
	}

	return tipo;
}

void MotorDeJuego::coronar(Posicion posicion)
{
	std::cout <<"Seleccione la pieza a la que se corona:\n\t1. Caballo\n\t2. Alfil\n\t3. Torre\n\t4. Dama\n";

	switch (getSelection())
	{
	case Pieza::tipo_t::PEON:
		tablero.escribir(posicion, new Peon(tablero, tablero.leer(posicion)->getColor()));
		break;
	case Pieza::tipo_t::CABALLO:
		tablero.escribir(posicion, new Caballo(tablero, tablero.leer(posicion)->getColor()));
		break;
	case Pieza::tipo_t::ALFIL:
		tablero.escribir(posicion, new Alfil(tablero, tablero.leer(posicion)->getColor()));
		break;
	case Pieza::tipo_t::TORRE:
		tablero.escribir(posicion, new Torre(tablero, tablero.leer(posicion)->getColor()));
		break;
	case Pieza::tipo_t::DAMA:
		tablero.escribir(posicion, new Dama(tablero, tablero.leer(posicion)->getColor()));
		break;
	case Pieza::tipo_t::REY:
		tablero.escribir(posicion, new Rey(tablero, tablero.leer(posicion)->getColor()));
		break;
	}
}

/////////////////

Movimiento MotorDeJuego::ensamblarMovimiento(Posicion posicion, bool pos1Selec) const
{
	static bool aux;
	static Posicion inicio;

	if (posicion != Posicion(-1, -1))
	{
		if (tablero.leer(posicion) != nullptr && tablero.leer(posicion)->getColor() == tablero.colorDelTurno)
		{
			inicio = posicion;
			pintar(posicion);
			aux = true;
		}
		else if (aux || pos1Selec)
		{
			aux = false;
			return Movimiento(inicio, posicion);
		}
	}

	return Movimiento(Posicion(), Posicion(-1, -1));
}