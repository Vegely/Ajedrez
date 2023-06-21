#include "MotorDeJuego.h"

#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Torre.h"
#include "Rey.h"
#include "Dama.h"

#include "IA.h"

#include "Mundo.h"

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

Movimiento MotorDeJuego::seleccionarEntrada(Mundo* p_motorGrafico)
{
	Movimiento movimiento = Movimiento();

	if (config[tablero.colorDelTurno] == ConfiguracionDeJuego::FormasDeInteraccion::IA)
		movimiento = IA::mover(tablero);
	else
	{
		if (config[tablero.colorDelTurno] == ConfiguracionDeJuego::FormasDeInteraccion::RECEPTOR)
		{
			std::string str;
			config.elementoRed->recibir(str);
			movimiento = Movimiento(str);
		}
		else
		{
			while(movimiento == Movimiento()) movimiento = ensamblarMovimiento(getInput(p_motorGrafico), p_motorGrafico);
			if (config[tablero.colorDelTurno] == ConfiguracionDeJuego::FormasDeInteraccion::EMISOR && movimiento.inicio != Posicion())
				config.elementoRed->enviar(movimiento.toString());
		}		
	}
	
	return movimiento;
}

void MotorDeJuego::pintarSeleccionCasilla(const Posicion& posSelec, Mundo* p_motorGrafico) const
{
	Pieza*		 pieza_leida      = tablero.leer(posSelec);
	Movimiento   ultima_jugada	  = tablero.getUltimaJugada();
	ListaModelo* lista_comer      = p_motorGrafico->getCasillaComible();
	ListaModelo* lista_coronacion = p_motorGrafico->getCasillaCoronacion();
	ListaModelo* lista_jugada	  = p_motorGrafico->getCasillaUltimoMov();
	ListaModelo* lista_mover	  = p_motorGrafico->getCasillaPuedeMover();
	ListaModelo* lista_seleccion  = p_motorGrafico->getCasillaSeleccionada();
	ListaModelo* lista_jaque	  = p_motorGrafico->getCasillaJaque();

	if (posSelec != Posicion() && pieza_leida != nullptr && tablero.leer(posSelec)->getColor() == tablero.colorDelTurno)
	{
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

DatosFinal MotorDeJuego::motor(Mundo* p_mundoGrafico)
{
	DatosFinal datosFinal;
	static Movimiento movimiento = Movimiento(Posicion(), Posicion());

	while (!exit)
	{
		comprobarCasillasJaque(p_mundoGrafico);
		p_mundoGrafico->antisolapamientoCasillas(tablero);

		movimiento = seleccionarEntrada(p_mundoGrafico);

		p_mundoGrafico->resetCasillas();

		if (movimiento.fin == Posicion()) 
			pintarSeleccionCasilla(movimiento.inicio, p_mundoGrafico);
		else if (tablero.hacerJugada(movimiento, config[tablero.colorDelTurno], p_mundoGrafico)) // Se hace la jugada
		{
			p_mundoGrafico->resetCasillas();
			
			fichero_partida->movimientos.push_back(tablero.ultimaJugada);

			if (tablero.jaqueMate())
			{
				comprobarCasillasJaque(p_mundoGrafico);
				datosFinal = { CodigoFinal::JAQUE_MATE, !tablero.colorDelTurno };
				datosFinal.finalizada = true;
				exit = true;
			}
			else if (tablero.reyAhogado())
			{
				datosFinal.codigoFinal = CodigoFinal::REY_AHOGADO;
				datosFinal.finalizada = true;
				exit = true;
			}
			else if (tablero.tablasMaterialInsuficiente())
			{
				datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_MATERIAL_INSUFICIENTE;
				datosFinal.finalizada = true;
				exit = true;
			}
			else if (tablero.infoTablas.tablasPorRepeticion())
			{
				datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_REPETICION;
				datosFinal.finalizada = true;
				exit = true;
			}
			else if (tablero.infoTablas.tablasPorPasividad())
			{
				datosFinal.codigoFinal = CodigoFinal::TABLAS_POR_PASIVIDAD;
				datosFinal.finalizada = true;
				exit = true;
			}
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

Movimiento MotorDeJuego::ensamblarMovimiento(Posicion posicion, Mundo* p_motorGrafico) const
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
		p_motorGrafico->getTableroJaqueMate()->copiar(tablero);

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