#include "MotorDeJuego.h"

constexpr auto NUM_LINEAS = 40;

////////////////////////

#include <iostream>
#include <windows.h>

void MotorDeJuego::pintar(Posicion posSelec)
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
					if (aux.x < 0) tablero.mover(Movimiento(Posicion(0, movimiento.inicio.y), Posicion(3, movimiento.inicio.y)));
					else tablero.mover(Movimiento(Posicion(7, movimiento.inicio.y), Posicion(5, movimiento.inicio.y)));
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
		tablero.cambiarTurno();
		tablero.ultimaJugada = movimiento;
		tablero.mover(movimiento);
		pintar();

		return true;
	}

	return false;
}

Movimiento MotorDeJuego::ensamblarMovimiento(Posicion posicion, bool pos1Selec)
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