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
	switch (config[tablero.colorDelTurno])
	{
	case ConfiguracionDeJuego::FormasDeInteraccion::LOCAL:
		return ensamblarMovimiento(getInput(p_motorGrafico), pos1Selec);

	case ConfiguracionDeJuego::FormasDeInteraccion::IA:
		return IA::mover(tablero);
	}
}

DatosFinal MotorDeJuego::motor(Mundo* mundoGrafico)
{
	DatosFinal datosFinal;
	static Movimiento movimiento = Movimiento(Posicion(-1, -1), Posicion(-1, -1));
	bool exit = false;
	bool jugadaHecha = true;

	while (!exit)
	{
		movimiento = seleccionarEntrada(mundoGrafico, !jugadaHecha);
		//Movimiento movimiento = seleccionarEntrada(mundoGrafico, pos1Selec);

		if (movimiento != Movimiento(Posicion{ 0, 0 }, Posicion{ -1, -1 }))
		{
			jugadaHecha = tablero.hacerJugada(movimiento, config[tablero.colorDelTurno], mundoGrafico);

			if (jugadaHecha) // Se hace la jugada
			{
				//pintar();

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
			mundoGrafico->leerTablero(tablero);
		}
	}

	return datosFinal;
}

Pieza::tipo_t MotorDeJuego::seleccionarEntradaCoronar(const Movimiento& movimiento, const Tablero& tablero, const ConfiguracionDeJuego::FormasDeInteraccion& interaccion, Mundo* motorGrafico)
{
	switch (interaccion)
	{
	case ConfiguracionDeJuego::FormasDeInteraccion::LOCAL:
		motorGrafico->resetLectura();
		return motorGrafico->seleccionPiezaCoronacion(tablero.getTurno());

	case ConfiguracionDeJuego::FormasDeInteraccion::IA:
		return IA::coronar(tablero, movimiento);
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