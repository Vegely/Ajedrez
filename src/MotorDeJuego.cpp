#include "MotorDeJuego.h"

#include "Peon.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Torre.h"
#include "Rey.h"
#include "Dama.h"

#include "IA.h"
#include "Mundo.h"

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

//void MotorDeJuego::pintarSeleccionCasilla(const Posicion& posSelec, Mundo* p_motorGrafico) const
//{// CHANGE
//	Pieza*		  pieza_leida       = tablero.leer(posSelec);
//	Pieza::tipo_t tipo				= tipo;
//	Posicion	  posicion			= tablero.leer(posSelec)->getPosicion();
//	bool	      color				= tablero.leer(posSelec)->getColor();
//	Movimiento    ultima_jugada		= tablero.getUltimaJugada();
//	ListaModelo*  lista_comer       = lista_comer;
//	ListaModelo*  lista_coronacion	= lista_coronacion;
//	ListaModelo*  lista_jugada		= p_motorGrafico->getCasillaUltimoMov();
//	ListaModelo*  lista_mover		= lista_mover;
//	ListaModelo*  lista_seleccion	= p_motorGrafico->getCasillaSeleccionada();
//
//	// for (int i = 0; i < 64; i++) if (posSelec != Posicion(-1, -1))
//	// {
//	// 	bool skip = false;
//
//	// 	if (Posicion(i % 8, i / 8) == posSelec)
//	// 	{
//
//	// 	}
//	// 	else
//	// 	{
//	// 		for (Posicion puedeMover : tablero.leer(posSelec)->getPuedeMover()) if (Posicion(i % 8, i / 8) == puedeMover)
//	// 		{
//	// 			if (tipo != Pieza::tipo_t::PEON || (puedeMover.x - posicion.x == 0))
//	// 			{
//	// 				if (tipo == Pieza::tipo_t::PEON &&
//	// 					((posSelec.y == 6 &&  color) || (posSelec.y == 1 && !color)))
//	// 				{
//	// 					lista_coronacion->moverElemento(Movimiento(Posicion(-1, -1), puedeMover)); // Seleccion de movimento 
//	// 					if (ultima_jugada.inicio == puedeMover || ultima_jugada.fin == puedeMover)
//	// 						lista_jugada->moverElemento(Movimiento(puedeMover, Posicion(-1, -1)));
//	// 					skip = true;
//	// 					break;
//	// 				}
//	// 				else if (tipo == Pieza::tipo_t::REY && abs(posSelec.x - puedeMover.x) == 2)
//	// 				{
//	// 					lista_coronacion->moverElemento(Movimiento(Posicion(-1, -1), puedeMover)); // Seleccion de movimento 
//	// 					if (ultima_jugada.inicio == puedeMover || ultima_jugada.fin == puedeMover)
//	// 						lista_jugada->moverElemento(Movimiento(puedeMover, Posicion(-1, -1)));
//	// 					skip = true;
//	// 					break;
//	// 				}
//	// 				lista_mover->moverElemento(Movimiento(Posicion(-1, -1), puedeMover)); // Seleccion de movimento 
//	// 				if (ultima_jugada.inicio == puedeMover || ultima_jugada.fin == puedeMover)
//	// 					lista_jugada->moverElemento(Movimiento(puedeMover, Posicion(-1, -1)));
//	// 				skip = true;
//	// 				break;
//	// 			}
//	if (posSelec != Posicion() && tablero.leer(posSelec) != nullptr && tablero.leer(posSelec)->getColor() == tablero.colorDelTurno)
//	{
//		for (int i = 0; i < 64; i++)
//		{
//		bool skip = false;
//		
//			if (Posicion(i % 8, i / 8) == posSelec)
//			{
//				p_motorGrafico->getCasillaSeleccionada()->moverElemento(Movimiento(Posicion(), posSelec)); // Seleccion de la pieza
//				if (tablero.getUltimaJugada().inicio == posSelec || tablero.getUltimaJugada().fin == posSelec)
//					p_motorGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(posSelec, Posicion()));
//			}
//
//			if (!skip && tablero.leer(Posicion(i % 8, i / 8)) != nullptr)
//			{
//				for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer())
//				{
//					if (Posicion(i % 8, i / 8) == puedeComer->getPosicion())
//					{
//						if (tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON && ((posSelec.y == 6 && tablero.leer(posSelec)->getColor()) || (posSelec.y == 1 && !tablero.leer(posSelec)->getColor())))
//						{// CHANGE
//							// lista_coronacion->moverElemento(Movimiento(Posicion(-1, -1), puedeComer->getPosicion())); // Seleccion de movimento 
//							// if (ultima_jugada.inicio == puedeComer->getPosicion() || ultima_jugada.fin == puedeComer->getPosicion())
//							// 	lista_jugada->moverElemento(Movimiento(puedeComer->getPosicion(), Posicion(-1, -1)));
//							if (tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON && ((posSelec.y == 6 && tablero.leer(posSelec)->getColor()) || (posSelec.y == 1 && !tablero.leer(posSelec)->getColor())))
//							{
//								lista_coronacion->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion())); // Seleccion de movimento 
//								if (tablero.getUltimaJugada().inicio == puedeComer->getPosicion() || tablero.getUltimaJugada().fin == puedeComer->getPosicion())
//									p_motorGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(puedeComer->getPosicion(), Posicion()));
//								skip = true;
//								break;
//							}
//							p_motorGrafico->getCasillaPuedeMover()->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion())); // Seleccion de movimento 
//							if (tablero.getUltimaJugada().inicio == puedeComer->getPosicion() || tablero.getUltimaJugada().fin == puedeComer->getPosicion())
//								p_motorGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(puedeComer->getPosicion(), Posicion()));
//							skip = true;
//							break;
//						}
//						if (!(tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON && puedeComer->getPosicion().y == posSelec.y))
//						{
//							lista_comer->moverElemento(Movimiento(Posicion(-1, -1), puedeComer->getPosicion())); // Seleccion de la comida
//							if (ultima_jugada.inicio == puedeComer->getPosicion() || ultima_jugada.fin == puedeComer->getPosicion())
//								lista_jugada->moverElemento(Movimiento(puedeComer->getPosicion(), Posicion(-1, -1)));
//						}
//						skip = true;
//						break;
//					}
//				}
//			}
//
//			if (!skip && tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON)
//			{
//				for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer())
//				{ // CHANGE
//					// if (puedeComer->getPosicion().y == posSelec.y && Posicion(i % 8, i / 8) == puedeComer->getPosicion() + (1 - 2 * !tablero.leer(posSelec)->getColor()) * Posicion(0, 1))
//					for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer())
//						if (Posicion(i % 8, i / 8) == puedeComer->getPosicion())
//						{
//							if (tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON && ((posSelec.y == 6 && tablero.leer(posSelec)->getColor()) || (posSelec.y == 1 && !tablero.leer(posSelec)->getColor())))
//							{
//								p_motorGrafico->getCasillaCoronacion()->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion())); // Seleccion de movimento 
//								if (tablero.getUltimaJugada().inicio == puedeComer->getPosicion() || tablero.getUltimaJugada().fin == puedeComer->getPosicion())
//									p_motorGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(puedeComer->getPosicion(), Posicion()));
//								skip = true;
//								break;
//							}
//							if (!(tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON && puedeComer->getPosicion().y == posSelec.y))
//							{
//								lista_comer->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion())); // Seleccion de la comida
//								if (tablero.getUltimaJugada().inicio == puedeComer->getPosicion() || tablero.getUltimaJugada().fin == puedeComer->getPosicion())
//									p_motorGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(puedeComer->getPosicion(), Posicion()));
//							}
//							skip = true;
//							break;
//						}
//				}
//
//				if (!skip && tablero.leer(posSelec)->getTipo() == Pieza::tipo_t::PEON)
//				{
//					for (Pieza* puedeComer : tablero.leer(posSelec)->getPuedeComer())
//					{
//						if (puedeComer->getPosicion().y == 4 && tablero.leer(posSelec)->getColor())
//						{// CHANGE
//							// lista_comer->moverElemento(Movimiento(Posicion(-1, -1), puedeComer->getPosicion() + Posicion(0, 1))); // Seleccion de la comida en pasada
//							// if (ultima_jugada.inicio == puedeComer->getPosicion() + Posicion(0, 1) || ultima_jugada.fin == puedeComer->getPosicion() + Posicion(0, 1))
//							// 	lista_jugada->moverElemento(Movimiento(puedeComer->getPosicion() + Posicion(0, 1), Posicion(-1, -1)));
//							if (puedeComer->getPosicion().y == 4 && tablero.leer(posSelec)->getColor())
//							{
//								lista_comer->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion() + Posicion(0, 1))); // Seleccion de la comida en pasada
//								if (tablero.getUltimaJugada().inicio == puedeComer->getPosicion() + Posicion(0, 1) || tablero.getUltimaJugada().fin == puedeComer->getPosicion() + Posicion(0, 1))
//									p_motorGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(puedeComer->getPosicion() + Posicion(0, 1), Posicion()));
//							}
//							else if (puedeComer->getPosicion().y == 3 && !tablero.leer(posSelec)->getColor())
//							{
//								lista_comer->moverElemento(Movimiento(Posicion(), puedeComer->getPosicion() + Posicion(0, -1))); // Seleccion de la comida en pasada
//								if (tablero.getUltimaJugada().inicio == puedeComer->getPosicion() + Posicion(0, -1) || tablero.getUltimaJugada().fin == puedeComer->getPosicion() + Posicion(0, -1))
//									p_motorGrafico->getCasillaUltimoMov()->moverElemento(Movimiento(puedeComer->getPosicion() + Posicion(0, -1), Posicion()));
//							}
//							break;
//						}
//						else if (puedeComer->getPosicion().y == 3 && !tablero.leer(posSelec)->getColor())
//						{
//							lista_comer->moverElemento(Movimiento(Posicion(-1, -1), puedeComer->getPosicion() + Posicion(0, -1))); // Seleccion de la comida en pasada
//							if (ultima_jugada.inicio == puedeComer->getPosicion() + Posicion(0, -1) || ultima_jugada.fin == puedeComer->getPosicion() + Posicion(0, -1))
//								lista_jugada->moverElemento(Movimiento(puedeComer->getPosicion() + Posicion(0, -1), Posicion(-1, -1)));
//						}
//						break;
//					}
//				}
//			}
//		}
//	}
//}

void MotorDeJuego::pintarSeleccionCasilla(const Posicion& posSelec, Mundo* p_motorGrafico) const
{
	Pieza*		  pieza_leida       = tablero.leer(posSelec);
	Movimiento    ultima_jugada		= tablero.getUltimaJugada();
	ListaModelo*  lista_comer       = p_motorGrafico->getCasillaComible();
	ListaModelo*  lista_coronacion	= p_motorGrafico->getCasillaCoronacion();
	ListaModelo*  lista_jugada		= p_motorGrafico->getCasillaUltimoMov();
	ListaModelo*  lista_mover		= p_motorGrafico->getCasillaPuedeMover();
	ListaModelo*  lista_seleccion	= p_motorGrafico->getCasillaSeleccionada();

	if (posSelec != Posicion() && pieza_leida != nullptr && tablero.leer(posSelec)->getColor() == tablero.colorDelTurno)
	{
		Pieza::tipo_t tipo = tablero.leer(posSelec)->getTipo();
		Posicion posicion = tablero.leer(posSelec)->getPosicion();
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
	bool exit = false;

	while (!exit)
	{
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
				datosFinal = { CodigoFinal::JAQUE_MATE, !tablero.colorDelTurno };
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

		p_mundoGrafico->leerTablero(tablero);
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
			/*p_motorGrafico->resetCasillas();
			pintarSeleccionCasilla(posicion, p_motorGrafico);*/
			aux = true;
			
		}
		else if (aux)
		{
			aux = false;
			/*std::cout << "Movimiento: ";
			std::cout << inicio.x << inicio.y << " a ";
			std::cout << posicion.x << posicion.y << std::endl;*/
			///
			/*p_motorGrafico->resetCasillas();*/
			return Movimiento(inicio, posicion);
		}

		// DEBUG
		/*static Posicion auxPos = posicion;
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
		auxPos = posicion;*/
		// DEBUG
	}

	return Movimiento(posicion, Posicion()); 
}

void MotorDeJuego::comprobarCasillasJaque(Mundo* motorGrafico)
{
	ListaModelo* lista_jaque = motorGrafico->getCasillaJaque();
	static bool flag = false;
	static bool flag_mate = false;
	static Movimiento ultima_jugada = Movimiento();

	if (ultima_jugada != tablero.getUltimaJugada())
	{
		flag = false;
		flag_mate = false;
		lista_jaque->setPosicion(Posicion(-1, -1)); // Mueve todas las casillas rojas a su posicion inicial;
	}

	if (tablero.leer(tablero.getReyPos( tablero.getTurno()))->getAmenazas().size() +
		tablero.leer(tablero.getReyPos(!tablero.getTurno()))->getAmenazas().size() != 0 && !flag) // Jaque / Jaque Mate
	{
		if (tablero.leer(tablero.getReyPos(tablero.getTurno()))->getAmenazas().size() != 0)
			lista_jaque->moverElemento(Movimiento(Posicion(-1, -1), tablero.getReyPos(tablero.getTurno()))); // Mover casilla roja
		else
			lista_jaque->moverElemento(Movimiento(Posicion(-1, -1), tablero.getReyPos(!tablero.getTurno()))); // Mover casilla roja

		if (tablero.jaqueMate() && !flag_mate)
		{
			for (Pieza* i : tablero.leer(tablero.getReyPos(tablero.getTurno()))->getAmenazas())
				lista_jaque->moverElemento(Movimiento(Posicion(-1, -1), i->getPosicion()));
			flag_mate = true;
		}
		std::cout << "Casilla: " << tablero.getReyPos(tablero.getTurno()).x << tablero.getReyPos(tablero.getTurno()).y << std::endl;
		std::cout << "Casilla valida: " << (tablero.leer(tablero.getReyPos(tablero.getTurno())) != nullptr) << std::endl;
		std::cout << "Es rey: " << (tablero.leer(tablero.getReyPos(tablero.getTurno()))->getTipo() == Pieza::tipo_t::REY) << std::endl;
		std::cout << "Amenazas: " << tablero.leer(tablero.getReyPos(tablero.getTurno()))->getAmenazas().size() << std::endl;
		flag = true;
	}
	ultima_jugada = tablero.getUltimaJugada();
}