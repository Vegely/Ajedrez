#include "MotorDeJuego.h"

#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Torre.h"
#include "Rey.h"
#include "Dama.h"

#include "IA.h"

constexpr auto NUM_LINEAS = 40;

//////////////////
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

Posicion getInput()
{
	string input;

	cin >> input;
 

	int letra = toupper(input[0]) - 65;
	int numero = input[1] - 49;
	if (letra >= 0 && letra < 8 && numero >= 0 && numero < 8) return Posicion(letra, numero);

	return Posicion(-1, -1);
}
//////////////////

Movimiento MotorDeJuego::seleccionarEntrada(bool pos1Selec) const
{
	switch (config[tablero.colorDelTurno])
	{
	case ConfiguracionDeJuego::FormasDeInteraccion::LOCAL:
		return ensamblarMovimiento(getInput(), pos1Selec);
	case ConfiguracionDeJuego::FormasDeInteraccion::IA:
		return IA::mover(tablero);
	}
}

DatosFinal MotorDeJuego::motor()
{
	DatosFinal datosFinal;
	bool exit = false;
	bool jugadaHecha = true;

	//seleccionarEntradaCoronar(Posicion(6, 6), tablero, config[0]);

	while (!exit)
	{
		Movimiento movimiento = seleccionarEntrada(!jugadaHecha);

		if (movimiento != Movimiento(Posicion(), Posicion(-1, -1))) // Se hace la jugada
		{
			jugadaHecha = tablero.hacerJugada(movimiento, config[tablero.colorDelTurno]);

			if (jugadaHecha) // Se hace la jugada
			{
				pintar();

				///
				if (tablero.numeroPiezas < 13)
					std::cout << "vrnoewbn" << std::endl;
				///

				if (tablero.jaqueMate())
				{ 
					datosFinal = { CodigoFinal::JAQUE_MATE, !tablero.colorDelTurno };
					exit = true;
				}
				else if (tablero.reyAhogado())
				{
					datosFinal.codigoFinal = CodigoFinal::REY_AHOGADO;
					exit = true;
				}
				else if (tablero.tablasMaterialInsuficiente())
				{
					datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_MATERIAL_INSUFICIENTE;
					exit = true;
				}
				else if (tablero.infoTablas.tablasPorRepeticion())
				{
					datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_REPETICION;
					exit = true;
				}
				else if (tablero.infoTablas.tablasPorPasividad())
				{
					datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_PASIVIDAD;
					exit = true;
				}
			}
		}
	}

	return datosFinal;
}



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

		if (i % 8 == 0) std::cout << "  " << j++ << "\t"; // Pintar los numeros

		bool skip = false;
		if (posSelec != Posicion(-1, -1)) // Seleccionar el color de fondo
		{
			if (Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == posSelec)
				SetConsoleTextAttribute(hStdout, 160); // Seleccion de la pieza
			else
			{
				for (Posicion puedeMover : tablero.leer(posSelec)->getPuedeMover()) if (Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == puedeMover)
					if (tablero.leer(posSelec)->getTipo() != Pieza::tipo_t::PEON || (puedeMover - tablero.leer(posSelec)->getPosicion()).x == 0)
					{
						SetConsoleTextAttribute(hStdout, 176); // Seleccion de movimento 
						skip = true;
						break;
					}

				if (!skip && tablero.leer(Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO)) != nullptr)
				{
					for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer())
						if (Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == puedeComer->getPosicion() )
						{
							if (!(tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON && puedeComer->getPosicion().y == posSelec.y)) 
								SetConsoleTextAttribute(hStdout, 64); // Seleccion de la comida
							skip = true;
							break;
						}
				}
				
				if (!skip && tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON) for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer())
					if (puedeComer->getPosicion().y == posSelec.y && Posicion(x % ANCHO_TABLERO, x / ANCHO_TABLERO) == puedeComer->getPosicion() + (1 - 2 * !tablero.leer(posSelec)->getColor()) * Posicion(0, 1))
					{
						SetConsoleTextAttribute(hStdout, 64); // Seleccion de la comida en pasada
						break;
					}
			}
		}
		
		if (tablero.tablero[x] == nullptr) std::cout << "---\t"; // Pintar vacio
		else std::cout << tablero.tablero[x]->getNombre() << " " << tablero.tablero[x]->getColor() << "\t"; // Pintar pieza

		SetConsoleTextAttribute(hStdout, 7); // Color de fondo

		if (i++ % 8 == 7) std::cout << "\n\n\n"; // L�neas de division de fila
	}

	std::cout << "\t";
	for (char i = 'A'; i <= 'H'; i++) std::cout << " " << i << " \t"; // Pintar las letras
	std::cout << std::endl;
}

////////////////////////

//bool MotorDeJuego::hacerJugada(Movimiento movimiento, Tablero& tablero, const ConfiguracionDeJuego& config)
//{
//	bool jugadaHecha = false;
//
//	for (const Pieza* puedeComer : tablero.leer(movimiento.inicio)->getPuedeComer())
//	{
//		if (puedeComer->getPosicion() == movimiento.fin)
//		{
//			if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON && puedeComer->getPosicion().y == movimiento.inicio.y);
//			else
//			{
//				tablero.actualizarHaMovido(movimiento);
//
//				delete tablero.leer(movimiento.fin);
//
//				tablero.infoTablas.clear();
//				tablero.numeroPiezas--;
//
//				jugadaHecha = true;
//				break;
//			}
//		}
//
//		if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON)
//		{
//			Posicion aux = puedeComer->getPosicion() + (1 - 2 * !tablero.leer(movimiento.inicio)->getColor()) * Posicion(0, 1);
//			if (aux == movimiento.fin)
//			{
//				tablero.actualizarHaMovido(movimiento);
//
//				tablero.tablero[puedeComer->getPosicion().indice()] = nullptr;
//				delete tablero.leer(aux);
//
//				tablero.infoTablas.clear();
//				tablero.numeroPiezas--;
//
//				jugadaHecha = true;
//				break;
//			}
//		}
//	}
//		
//	if (!jugadaHecha) for (const Posicion puedeMover : tablero.leer(movimiento.inicio)->getPuedeMover())
//	{
//		if (puedeMover == movimiento.fin)
//		{ 
//			if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::REY)
//			{
//				Posicion aux = movimiento.fin - movimiento.inicio;
//				if (abs(aux.x) == 2)
//				{
//					if (aux.x < 0) tablero.mover(Movimiento(Posicion(0, movimiento.inicio.y), Posicion(3, movimiento.inicio.y)));
//					else tablero.mover(Movimiento(Posicion(7, movimiento.inicio.y), Posicion(5, movimiento.inicio.y)));
//
//					tablero.infoTablas.clear();
//				}	
//			}
//
//			tablero.actualizarHaMovido(movimiento);
//
//			jugadaHecha = true; 
//			break; 
//		}
//	}
//		
//
//	if (jugadaHecha)
//	{
//		if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON && movimiento.fin.y % 7 == 0)
//		{
//			Pieza* p_pieza = tablero.leer(movimiento.inicio);
//			tablero.coronar(movimiento.inicio, seleccionarEntradaCoronar(movimiento.inicio, tablero, config));
//			delete p_pieza;
//		}
//
//		tablero.cambiarTurno();
//		tablero.ultimaJugada = movimiento;
//		tablero.mover(movimiento);
//
//		return true;
//	}
//
//	return false;
//}

/////////////////

#include <string>

Pieza::tipo_t getSelection()
{
	std::cout <<"Seleccione la pieza a la que se corona:\n\t1. Caballo\n\t2. Alfil\n\t3. Torre\n\t4. Dama\n";
	
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

/////////////////
Pieza::tipo_t MotorDeJuego::seleccionarEntradaCoronar(const Posicion& posicion, const Tablero& tablero, const ConfiguracionDeJuego::FormasDeInteraccion& interaccion)
{
	switch (interaccion)
	{
	case ConfiguracionDeJuego::FormasDeInteraccion::LOCAL:
		return getSelection();
	case ConfiguracionDeJuego::FormasDeInteraccion::IA:
		return IA::coronar(tablero, posicion);
	}
}

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