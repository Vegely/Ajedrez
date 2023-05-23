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
				for (Posicion puedeMover : tablero.leer(posSelec)->getPuedeMover()) if (Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == puedeMover) SetConsoleTextAttribute(hStdout, 176);
				for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer()) if (Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == puedeComer->getPosicion()) SetConsoleTextAttribute(hStdout, 64);
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
	for (const Posicion puedeMover : tablero.leer(movimiento.inicio)->getPuedeMover())
	{
		if (puedeMover == movimiento.fin)
		{
			tablero.mover(movimiento);
			tablero.cambiarTurno();
			pintar();

			return true;
		}
	}

	for (const Pieza* puedeComer : tablero.leer(movimiento.inicio)->getPuedeComer())
	{
		if (puedeComer->getPosicion() == movimiento.fin)
		{
			if (tablero.leer(movimiento.fin) != nullptr)
			{
				delete tablero.leer(movimiento.fin);
			}

			tablero.mover(movimiento);
			tablero.cambiarTurno();
			pintar();

			return true;
		}
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