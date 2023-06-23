#include "MotorDeJuego.h"

#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Torre.h"
#include "Rey.h"
#include "Dama.h"

#include "IA.h"

#include <cstdint>
#include <chrono>

#define TIEMPO_MS_MIN_MOVIMIENTO 150

///
#include <iostream>
///

constexpr auto NUM_LINEAS = 40;

Posicion getInput(Mundo* p_motorGrafico) 
{
	static Posicion pos;
	
	if (pos != p_motorGrafico->getCasilla())
	{
		pos = p_motorGrafico->getCasilla();
		return pos;
	}
	
	return Posicion();
}


Movimiento MotorDeJuego::seleccionarEntrada(Mundo* p_motorGrafico, bool& run)
{	
	Movimiento movimiento = Movimiento();
	if (!fichero_partida.movimientosEntrada.empty()) 
	{
		movimiento = fichero_partida.movimientosEntrada.front();
		fichero_partida.movimientosEntrada.pop_front();
	}
	else if (config[tablero.colorDelTurno] == ConfiguracionDeJuego::FormasDeInteraccion::IA)
		movimiento = IA::mover(*this);
	else
	{
		if (config[tablero.colorDelTurno] == ConfiguracionDeJuego::FormasDeInteraccion::RECEPTOR)
		{
			while(elementoRed.recibido.empty() && run); // Esperar hasta que se reciba algo
			movimiento = Movimiento(elementoRed.recibido);
			elementoRed.recibido.clear();
		}
		else
		{
			while(movimiento == Movimiento()) 
			{
				if (!run) return Movimiento();
				movimiento = ensamblarMovimiento(getInput(p_motorGrafico));
			}

			if (config[tablero.colorDelTurno] == ConfiguracionDeJuego::FormasDeInteraccion::EMISOR)
				elementoRed.enviar(movimiento.toString());
		}		
	}
	
	return movimiento;
}

void MotorDeJuego::pintarSeleccionCasilla(const Posicion& posSelec, Mundo* p_motorGrafico) const
{
	if (posSelec != Posicion() && tablero.leer(posSelec) != nullptr && tablero.leer(posSelec)->getColor() == tablero.colorDelTurno)
	{
		Movimiento   ultima_jugada	  = tablero.getUltimaJugada();
		ListaModelo* lista_comer      = p_motorGrafico->getCasillaComible();
		ListaModelo* lista_coronacion = p_motorGrafico->getCasillaCoronacion();
		ListaModelo* lista_jugada	  = p_motorGrafico->getCasillaUltimoMov();
		ListaModelo* lista_mover	  = p_motorGrafico->getCasillaPuedeMover();
		ListaModelo* lista_seleccion  = p_motorGrafico->getCasillaSeleccionada();
		ListaModelo* lista_jaque	  = p_motorGrafico->getCasillaJaque();

		Pieza::tipo_t tipo = tablero.leer(posSelec)->getTipo();
		Posicion posicion  = tablero.leer(posSelec)->getPosicion();
		bool color = tablero.leer(posSelec)->getColor();
		for (int i = 0; i < 64; i++)
		{
			bool skip = false;

			if (Posicion(i % 8, i / 8) == posSelec)
			{
				lista_seleccion->moverElemento(Movimiento(Posicion(), posSelec)); // Seleccion de la pieza
				if (ultima_jugada.inicio == posSelec || ultima_jugada.fin == posSelec)
					lista_jugada->moverElemento(Movimiento(posSelec, Posicion()));
			}

			else
			{
				for (Posicion puedeMover : tablero.leer(posSelec)->getPuedeMover())
				{
					if (Posicion(i % 8, i / 8) == puedeMover)
					{
						if (tipo != Pieza::tipo_t::PEON || (puedeMover - tablero.leer(posSelec)->getPosicion()).x == 0)
						{
							if (tipo == Pieza::tipo_t::PEON && ((posSelec.y == 6 && color) || (posSelec.y == 1 && !color)))
							{
								lista_coronacion->moverElemento(Movimiento(Posicion(), puedeMover)); // Seleccion de movimento 
								if (ultima_jugada.inicio == puedeMover || ultima_jugada.fin == puedeMover)
									lista_jugada->moverElemento(Movimiento(puedeMover, Posicion()));
								skip = true;
								break;
							}
							lista_mover->moverElemento(Movimiento(Posicion(), puedeMover)); // Seleccion de movimento 
							if (ultima_jugada.inicio == puedeMover || ultima_jugada.fin == puedeMover)
								lista_jugada->moverElemento(Movimiento(puedeMover, Posicion()));
							if (tipo == Pieza::tipo_t::REY && (((puedeMover == Posicion(6, 0) || puedeMover == Posicion(2, 0)) && color) || ((puedeMover == Posicion(6, 7) || puedeMover == Posicion(2, 7)) && !color)))
							{
								lista_mover->moverElemento(Movimiento(puedeMover, Posicion()));
								lista_coronacion->moverElemento(Movimiento(Posicion(), puedeMover));
							}
							skip = true;
							break;
						}
					}
				}

				if (!skip && tablero.leer(Posicion(i % 8, i / 8)) != nullptr)
				{
					for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer())
						if (Posicion(i % 8, i / 8) == puedeComer->getPosicion())
						{
							if (tipo == Pieza::tipo_t::PEON && ((posSelec.y == 6 && color) || (posSelec.y == 1 && !color)))
							{
								lista_coronacion->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion())); // Seleccion de movimento 
								if (ultima_jugada.inicio == puedeComer->getPosicion() || ultima_jugada.fin == puedeComer->getPosicion())
									lista_jugada->moverElemento(Movimiento(puedeComer->getPosicion(), Posicion()));
								skip = true;
								break;
							}
							if (!(tipo == Pieza::tipo_t::PEON && puedeComer->getPosicion().y == posSelec.y))
							{
								lista_comer->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion())); // Seleccion de la comida
								if (ultima_jugada.inicio == puedeComer->getPosicion() || ultima_jugada.fin == puedeComer->getPosicion())
									lista_jugada->moverElemento(Movimiento(puedeComer->getPosicion(), Posicion()));
							}
							skip = true;
							break;
						}
				}

				if (!skip && tipo == Pieza::tipo_t::PEON)
				{
					for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer())
					{
						if (puedeComer->getPosicion().y == posSelec.y && Posicion(i % 8, i / 8) == puedeComer->getPosicion() + (1 - 2 * !color) * Posicion(0, 1))
						{
							if (puedeComer->getPosicion().y == 4 && color)
							{
								lista_comer->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion() + Posicion(0, 1))); // Seleccion de la comida en pasada
								if (ultima_jugada.inicio == puedeComer->getPosicion() + Posicion(0, 1) || ultima_jugada.fin == puedeComer->getPosicion() + Posicion(0, 1))
									lista_jugada->moverElemento(Movimiento(puedeComer->getPosicion() + Posicion(0, 1), Posicion()));
							}
							else if (puedeComer->getPosicion().y == 3 && !color)
							{
								lista_comer->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion() + Posicion(0, -1))); // Seleccion de la comida en pasada
								if (ultima_jugada.inicio == puedeComer->getPosicion() + Posicion(0, -1) || ultima_jugada.fin == puedeComer->getPosicion() + Posicion(0, -1))
									lista_jugada->moverElemento(Movimiento(puedeComer->getPosicion() + Posicion(0, -1), Posicion()));
							}
							break;
						}
					}
				}
			}
		}
	}
}

uint64_t getTimeSinceEpoch()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

DatosFinal MotorDeJuego::motor(Mundo* p_mundoGrafico, bool& run)
{
	// Reset
	//p_mundoGrafico->resetLectura();
	p_mundoGrafico->resetCasillas();

	// Pintar tablero
	p_mundoGrafico->leerTablero(&tablero);
	p_mundoGrafico->actualizarCamara(tablero.colorDelTurno, TIMEPO_ROTACION_CAMARA, config);
	
	DatosFinal datosFinal;
	long long int t0 = getTimeSinceEpoch(); // Tomar timepo para el primer movimiento
	while (!datosFinal.finalizada)
	{
		// Entrada del movimiento
		Movimiento movimiento = seleccionarEntrada(p_mundoGrafico, run);
		if (!run) return DatosFinal(); // Salir a mitad de partida

		p_mundoGrafico->resetCasillas();		

		if (movimiento.fin == Posicion()) // Pintar seleccion de pieza
			pintarSeleccionCasilla(movimiento.inicio, p_mundoGrafico);
		else if (tablero.hacerJugada(*this, movimiento, config[tablero.colorDelTurno], p_mundoGrafico, run, true)) // Se hace la jugada
		{
			// Guardar el movimiento
			fichero_partida.movimientosSalida.push_back(tablero.ultimaJugada);

			// Evitar que se mueva muy rapido
			while (getTimeSinceEpoch() - t0 < TIEMPO_MS_MIN_MOVIMIENTO); // Evita hacer un movimiento en menos tiempo que TIEMPO_MIN_MOVIMIENTO
			t0 = getTimeSinceEpoch();
			
			// Pintar tablero
			p_mundoGrafico->leerTablero(&tablero);
			comprobarCasillasJaque(p_mundoGrafico);

			// Resetear la ultima posicion pulsada
			p_mundoGrafico->resetLectura();

			// Comprobar finales
			if (tablero.jaqueMate())
				datosFinal = DatosFinal{ CodigoFinal::JAQUE_MATE, true, !tablero.colorDelTurno };
			else if (tablero.reyAhogado())
				datosFinal = DatosFinal{ CodigoFinal::REY_AHOGADO, true };
			else if (tablero.tablasMaterialInsuficiente())
				datosFinal = DatosFinal{ CodigoFinal::TABLAS_POR_MATERIAL_INSUFICIENTE, true };
			else if (tablero.infoTablas.tablasPorRepeticion())
				datosFinal = DatosFinal{ CodigoFinal::TABLAS_POR_REPETICION, true };
			else if (tablero.infoTablas.tablasPorPasividad())
				datosFinal = DatosFinal{ CodigoFinal::TABLAS_POR_PASIVIDAD, true };

			// Rotar camara
			p_mundoGrafico->actualizarCamara(tablero.colorDelTurno, TIMEPO_ROTACION_CAMARA, config);
		}
		
		// Pintar ultimo movimiento
		p_mundoGrafico->resetCasillas(p_mundoGrafico->getCasillaUltimoMov());
		p_mundoGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(Posicion(), tablero.ultimaJugada.inicio));
		p_mundoGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(Posicion(), tablero.ultimaJugada.fin));
	}

	return datosFinal;
}

Pieza::tipo_t MotorDeJuego::seleccionarEntradaCoronar(MotorDeJuego& motor, const Movimiento& movimiento, const Tablero& tablero, const ConfiguracionDeJuego::FormasDeInteraccion& interaccion, Mundo* motorGrafico, bool& run, bool guardarCoronacion)
{
	Pieza::tipo_t tipo = Pieza::tipo_t::NULA;
	if (!motor.fichero_partida.coronacionEntrada.empty())
	{
		tipo = (Pieza::tipo_t)motor.fichero_partida.coronacionEntrada.front();
		motor.fichero_partida.coronacionEntrada.pop_front();
	}
	else if (interaccion == ConfiguracionDeJuego::FormasDeInteraccion::IA)
		tipo = IA::coronar(motor, tablero, movimiento);
	else
	{
		if (interaccion == ConfiguracionDeJuego::FormasDeInteraccion::RECEPTOR)
		{
			while (motor.elementoRed.recibido.empty() && run); // Esperar hasta que se reciba algo
			tipo = (Pieza::tipo_t)stoi(motor.elementoRed.recibido);
			motor.elementoRed.recibido.clear();
		}
		else
		{
			motorGrafico->resetLectura();
			while (tipo == Pieza::tipo_t::NULA)
			{
				if (!run) return Pieza::tipo_t::DAMA;
				tipo = motorGrafico->seleccionPiezaCoronacion(tablero.getTurno()); // Quitar el bucle interno
			}

			if (interaccion == ConfiguracionDeJuego::FormasDeInteraccion::EMISOR)
				motor.elementoRed.enviar(movimiento.toString());
		}
	}

	if (guardarCoronacion) motor.fichero_partida.coronacionSalida.push_back((int)tipo);

	return tipo;
}

Movimiento MotorDeJuego::ensamblarMovimiento(Posicion posicion) const
{
	static bool aux;
	static Posicion inicio;

	if (posicion != Posicion())
	{
		if (tablero.leer(posicion) != nullptr && tablero.leer(posicion)->getColor() == tablero.colorDelTurno)
		{
			inicio = posicion;
			aux = true;
		}
		else if (aux)
		{
			aux = false;
			return Movimiento(inicio, posicion);
		}
	}

	return Movimiento(posicion, Posicion()); 
}

void MotorDeJuego::comprobarCasillasJaque(Mundo* p_motorGrafico)
{
	p_motorGrafico->resetCasillas(p_motorGrafico->getCasillaJaque());
	if (&tablero != nullptr)
	{
		//p_motorGrafico->getTableroJaqueMate()->copiar(tablero);

		for (int i = 0; i < 64; i++)
		{
			Pieza* pieza_leida = tablero.leer(Posicion(i % 8, i / 8));
			ListaModelo* lista_jaque = p_motorGrafico->getCasillaJaque();

			if (pieza_leida != nullptr)
			{
				Pieza::tipo_t tipo = pieza_leida->getTipo();
				Posicion posicion = pieza_leida->getPosicion();

				if (tipo == Pieza::tipo_t::REY && pieza_leida->getAmenazas().size() > 0) // Jaque
				{
					lista_jaque->moverElemento(Movimiento(Posicion(), posicion));
					if (tablero.jaqueMate()) // Jaque Mate
					{
						for (int i = 0; i < pieza_leida->getAmenazas().size(); i++)
							lista_jaque->moverElemento(Movimiento(Posicion(), pieza_leida->getAmenazas()[i]->getPosicion()));
					}
				}
			}
		}
	}
}