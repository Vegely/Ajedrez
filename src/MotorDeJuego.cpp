#include "MotorDeJuego.h"

#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Torre.h"
#include "Rey.h"
#include "Dama.h"

#include "IA.h"
#include "Mundo.h"

#include <iostream>

constexpr auto NUM_LINEAS = 40;

using namespace std;

Posicion getInput(Mundo* p_motorGrafico) 
{
	Posicion pos = p_motorGrafico->getCasilla();
	if (pos.x >= 0 && pos.x < 8 && pos.y >= 0 && pos.y < 8) return pos;
	else return Posicion(-1, -1);
}

Movimiento MotorDeJuego::seleccionarEntrada(Mundo* p_motorGrafico, bool pos1Selec)
{
	Movimiento movimiento = Movimiento{ Posicion{0, 0}, Posicion{0, 0} };

	switch (config[tablero.colorDelTurno])
	{
	case ConfiguracionDeJuego::FormasDeInteraccion::LOCAL:
		movimiento = ensamblarMovimiento(getInput(p_motorGrafico), pos1Selec);
		break;

	case ConfiguracionDeJuego::FormasDeInteraccion::IA:
		movimiento = IA::mover(tablero);
		break;
	}

	return movimiento;
}

DatosFinal MotorDeJuego::motor(Mundo* mundoGrafico)
{
	DatosFinal datosFinal;
	bool exit = false;
	bool pos1Selec = false;

	while (!exit)
	{
		Movimiento movimiento = seleccionarEntrada(mundoGrafico, pos1Selec);

		if (movimiento != Movimiento(Posicion{ -1, -1 }, Posicion{ -1, -1 }))
		{
			if (movimiento != Movimiento(Posicion(), Posicion(-1, -1))) // Se hace la jugada
			{
				pos1Selec = !hacerJugada(movimiento, mundoGrafico);

				if (!pos1Selec) // Se hace la jugada
				{
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
			mundoGrafico->leerTablero(tablero);
		}
	}

	return datosFinal;
}

bool MotorDeJuego::hacerJugada(Movimiento movimiento, Mundo* motorGrafico)
{
	bool JugadaHecha = false;

	for (const Pieza* puedeComer : tablero.leer(movimiento.inicio)->getPuedeComer())
	{
		if (puedeComer->getPosicion() == movimiento.fin)
		{
			if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON && puedeComer->getPosicion().y == movimiento.inicio.y);
			else
			{
				tablero.actualizarHaMovido(movimiento);

				delete tablero.leer(movimiento.fin);

				tablero.infoTablas.clear();
				tablero.numeroPiezas--;

				JugadaHecha = true;
				break;
			}

		}

		if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON)
		{
			Posicion aux = puedeComer->getPosicion() + (1 - 2 * !tablero.leer(movimiento.inicio)->getColor()) * Posicion(0, 1);
			if (aux == movimiento.fin)
			{
				tablero.actualizarHaMovido(movimiento);

				tablero.tablero[puedeComer->getPosicion().indice()] = nullptr;
				delete tablero.leer(aux);

				tablero.infoTablas.clear();
				tablero.numeroPiezas--;

				JugadaHecha = true;
				break;
			}
		}
	}
		
	if (!JugadaHecha) for (const Posicion puedeMover : tablero.leer(movimiento.inicio)->getPuedeMover())
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

			JugadaHecha = true; 
			break; 
		}
	}
		

	if (JugadaHecha)
	{
		if (tablero.leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON && movimiento.fin.y % 7 == 0)
		{
			Pieza* p_pieza = tablero.leer(movimiento.inicio);
			tablero.coronar(movimiento.inicio, seleccionarEntradaCoronar(movimiento.inicio, motorGrafico));
			delete p_pieza;
		}

		tablero.cambiarTurno();
		tablero.ultimaJugada = movimiento;
		tablero.mover(movimiento);
		
		//pintar();

		return true;
	}

	return false;
}

Pieza::tipo_t getSelection(Mundo* motorGrafico)
{
	Pieza* pieza_coronacion = motorGrafico->getPiezaCoronacion();
	if (pieza_coronacion != nullptr)
	{
		switch (static_cast<int>(pieza_coronacion->getTipo()))
		{
		case 1:
			return Pieza::tipo_t::CABALLO;
			break;
		case 2:
			return Pieza::tipo_t::ALFIL;
			break;
		case 3:
			return Pieza::tipo_t::TORRE;
			break;
		case 4:
			return Pieza::tipo_t::DAMA;
			break;
		default:
			std::cout << "No es una pieza valida para coronar." << std::endl;
			return pieza_coronacion->getTipo();
			break;
		}
	}
}

Pieza::tipo_t MotorDeJuego::seleccionarEntradaCoronar(Posicion posicion, Mundo* motorGrafico) const
{
	Pieza::tipo_t tipo;

	switch (config[tablero.colorDelTurno])
	{
	case ConfiguracionDeJuego::FormasDeInteraccion::LOCAL:
		tipo = getSelection(motorGrafico);
		break;
	case ConfiguracionDeJuego::FormasDeInteraccion::IA:
		tipo = IA::coronar(tablero, posicion);
		break;
	}

	return tipo;
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
			//pintar(posicion);
			aux = true;
		}
		else if (aux || pos1Selec)
		{
			aux = false;
			std::cout << "Movimiento: ";
			std::cout << inicio.x << inicio.y << " a ";
			std::cout << posicion.x << posicion.y << std::endl;
			return Movimiento(inicio, posicion);
		}

		// DEBUG
		static Posicion auxPos = posicion;
		if (auxPos != posicion)
		{
			std::string color_turno = "";
			if (tablero.colorDelTurno) color_turno = "Blanco"; else color_turno = "Negro";
			std::cout << std::endl << "DEBUG ENSAMBLAR MOVIMIENTO:" << std::endl;
			std::cout << "Color del turno: " << color_turno << std::endl;
			std::cout << "Existe pieza: " << (tablero.leer(posicion) != nullptr) << std::endl;
			if (tablero.leer(posicion) != nullptr)
			{
				std::string tipo = "";
				std::string color = "";
				switch (static_cast<int>(tablero.leer(posicion)->getTipo()))
				{
				case 0:
					tipo = "PEON";
					break;
				case 1:
					tipo = "CABALLO";
					break;
				case 2:
					tipo = "ALFIL";
					break;
				case 3:
					tipo = "TORRE";
					break;
				case 4:
					tipo = "DAMA";
					break;
				case 5:
					tipo = "REY";
					break;
				default:
					break;
				}
				if (tablero.leer(posicion)->getColor()) color = "Blanco"; else color = "Negro";
				std::cout << "Pieza: " << tipo << std::endl;
				std::cout << "Color de la pieza: " << color << std::endl;
			}
			std::cout << "Posicion inicio: " << inicio.x << inicio.y << std::endl;
			std::cout << "Posicion actual: " << posicion.x << posicion.y << std::endl << std::endl;
		}
		auxPos = posicion;
		// DEBUG
	}

	return Movimiento(Posicion(), Posicion(-1, -1));
}