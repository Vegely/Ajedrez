#include <string>
#include <cmath>
#include <algorithm>

#include "Tablero.h"
#include "Caballo.h"
#include "Rey.h"
#include "Peon.h"
#include "Alfil.h"
#include "Torre.h"
#include "Dama.h"

#include "MotorDeJuego.h"

void Tablero::actualizarTablero()
{
	for (auto limpiezaUnasAOtras : tablero) {
		if (limpiezaUnasAOtras != nullptr)
		{
			limpiezaUnasAOtras->amenazas.clear();
			limpiezaUnasAOtras->esta_protegida.clear();
		}	
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				tableroIlegalesRey[i][j][k] = false;
			}
		}
	}

	datosClavada.clear();
	DatosClavada aux;

	for (Pieza* p_pieza : tablero) {


		if (p_pieza != nullptr) {
			aux = p_pieza->actualizarVariables(false, Posicion{ 0,0 }, tableroIlegalesRey);

			if (aux.ExisteClavada == true)
			{
				datosClavada.push_back(aux);
			}
		}

	}

	leer(reyPos[0])->actualizarVariables(false, Posicion{ 0,0 }, tableroIlegalesRey);
	leer(reyPos[1])->actualizarVariables(false, Posicion{ 0,0 }, tableroIlegalesRey);

	actualizarAlPaso();

	for (int i = 0; i < datosClavada.size(); i++) //Clavar las piezas clavadas
	{
		datosClavada[i].PiezaClavada->actualizarVariables(true, datosClavada[i].DireccionClavada,tableroIlegalesRey);
	}	

	actualizarEnroque();
	actualizarJaque();
}
Tablero::Tablero(bool alocar)
{
	for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++) { tablero[i] = nullptr; } //Se crea un tablero vacio

	
	if (alocar)
	{
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
		reyPos[1] = Posicion{ 4,0 };

		escribir(Posicion(3, 0), new Dama(*this, true));
		escribir(reyPos[1], new Rey(*this, true));

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
		
		//Se escribe la dama y el rey4
		reyPos[0] = Posicion{ 4, 7 };

		escribir(Posicion(3, 7), new Dama(*this, false));
		escribir(reyPos[0], new Rey(*this, false));
		
		colorDelTurno = true;

		actualizarTablero(); //Se inicializan los movimientos posibles
		numeroPiezas = 32;

		infoTablas.add(*this);

		///*True == Blancas <-> False == Negras En color
		//Blancas 
		//Se añaden los peones*/
		//escribir(Posicion(0, 3), new Peon(*this, true));
		//escribir(Posicion(3, 3), new Peon(*this, true));
		//
		////Se añaden las torres
		///*escribir(Posicion(0, 0), new Torre(*this, true));
		//escribir(Posicion(7, 0), new Torre(*this, true));*/

		////Se escriben los caballos
		//escribir(Posicion(4, 2), new Caballo(*this, true));
		////escribir(Posicion(6, 0), new Caballo(*this, true));

		////Se escriben los alfiles
		///*escribir(Posicion(2, 0), new Alfil(*this, true));
		//escribir(Posicion(5, 0), new Alfil(*this, true));*/
		//
		////Se escribe la dama y el rey
		//reyPos[1] = Posicion{ 6,0 };

		////escribir(Posicion(3, 0), new Dama(*this, true));
		//escribir(reyPos[1], new Rey(*this, true));

		////Negras
		////Se añaden los peones
		//escribir(Posicion(0, 6), new Peon(*this, false));
		//escribir(Posicion(3, 4), new Peon(*this, false));
		//escribir(Posicion(5, 4), new Peon(*this, false));
		//escribir(Posicion(6, 2), new Peon(*this, false));
		//escribir(Posicion(6, 7), new Peon(*this, false));
		//
		////Se añaden las torres
		////escribir(Posicion(0, 7), new Torre(*this, false));
		//escribir(Posicion(7, 7), new Torre(*this, false));

		////Se escriben los caballos
		//escribir(Posicion(2, 6), new Caballo(*this, false));
		////escribir(Posicion(6, 7), new Caballo(*this, false));

		////Se escriben los alfiles
		///*escribir(Posicion(2, 7), new Alfil(*this, false));
		//escribir(Posicion(5, 7), new Alfil(*this, false));*/
		//
		////Se escribe la dama y el rey4
		//reyPos[0] = Posicion{ 1, 3 };

		////escribir(Posicion(3, 7), new Dama(*this, false));
		//escribir(reyPos[0], new Rey(*this, false));

		/////
		//for (bool& i : haMovido) i = true;
		/////

		//colorDelTurno = false;

		//actualizarTablero(); //Se inicializan los movimientos posibles
		//numeroPiezas = 12;

		//infoTablas.add(*this);
	}
}

Tablero Tablero::copiar(const Tablero& tablero)
{
	Tablero aux;

	// Alocar la copia de las piezas en memoria
	for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++)
	{
		if (tablero.tablero[i] != nullptr)
		{
			switch (tablero.tablero[i]->tipo)
			{
			case Pieza::tipo_t::PEON:
				aux.escribir(tablero.posicion(i), new Peon(aux, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::CABALLO:
				aux.escribir(tablero.posicion(i), new Caballo(aux, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::ALFIL:
				aux.escribir(tablero.posicion(i), new Alfil(aux, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::TORRE:
				aux.escribir(tablero.posicion(i), new Torre(aux, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::DAMA:
				aux.escribir(tablero.posicion(i), new Dama(aux, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::REY:
				aux.escribir(tablero.posicion(i), new Rey(aux, tablero.tablero[i]->color));
				break;
			}

			*aux.tablero[i] = *tablero.tablero[i];
		}
		else aux.tablero[i] = nullptr;
	}

	//Copiar resto de variables
	aux.colorDelTurno = tablero.colorDelTurno;
	for (int i = 0; i < 2; i++) aux.reyPos[i] = tablero.reyPos[i];

	for (int i = 0; i < 6; i++) aux.haMovido[i] = tablero.haMovido[i];
		aux.numeroPiezas = tablero.numeroPiezas;
	for (int i = 0; i < 2; i++) for (int j = 0; j < 8; j++) for (int k = 0; k < 8; k++) aux.tableroIlegalesRey[i][j][k] = tablero.tableroIlegalesRey[i][j][k];
	for (int i = 0; i < tablero.datosClavada.size(); i++)
		aux.datosClavada.push_back(tablero.datosClavada.at(i));

	aux.ultimaJugada = tablero.ultimaJugada;
	
	aux.infoTablas = tablero.infoTablas;

	return aux;
}

void Tablero::escribir(const Posicion& posicion, Pieza* pieza)
{
	tablero[posicion.x + posicion.y * ANCHO_TABLERO] = pieza;
	if (pieza != nullptr) pieza->posicion = posicion;
}

void Tablero::mover(const Movimiento& movimiento) {
	escribir(movimiento.fin, leer(movimiento.inicio));
	escribir(movimiento.inicio, nullptr);

	if (leer(movimiento.fin)->tipo == Pieza::tipo_t::PEON) infoTablas.clear();
	infoTablas.add(*this);

	if (leer(movimiento.fin)->tipo == Pieza::tipo_t::REY)
	{
		reyPos[leer(movimiento.fin)->color] = movimiento.fin; // Si se mueve un rey acctualizar la variable reyPos
	}

	actualizarTablero();
}

bool Tablero::hacerJugada(const Movimiento& movimiento, const ConfiguracionDeJuego::FormasDeInteraccion& interaccion)
{
	bool jugadaHecha = false;

	for (const Pieza* puedeComer : leer(movimiento.inicio)->getPuedeComer())
	{
		if (puedeComer->getPosicion() == movimiento.fin)
		{
			// Se puede comer y no es un peon intentando comer en paralelo (Internamente eso es una comida al paso)
			if (leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON && puedeComer->getPosicion().y == movimiento.inicio.y);
			else
			{
				actualizarHaMovido(movimiento);

				delete leer(movimiento.fin);

				infoTablas.clear();
				numeroPiezas--;

				jugadaHecha = true;
				break;
			}
		}

		// Comer al paso
		if (leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON)
		{
			Posicion aux = puedeComer->getPosicion() + (1 - 2 * !leer(movimiento.inicio)->getColor()) * Posicion(0, 1);
			
			if (aux == movimiento.fin)
			{
				tablero[puedeComer->getPosicion().indice()] = nullptr;
				delete leer(aux);

				infoTablas.clear();
				numeroPiezas--;

				jugadaHecha = true;
				break;
			}
		}
	}

	if (!jugadaHecha) for (const Posicion puedeMover : leer(movimiento.inicio)->getPuedeMover())
	{
		if (puedeMover == movimiento.fin)
		{
			if (leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::REY)
			{
				Posicion aux = movimiento.fin - movimiento.inicio;
				if (abs(aux.x) == 2)
				{
					if (aux.x < 0) mover(Movimiento(Posicion(0, movimiento.inicio.y), Posicion(3, movimiento.inicio.y)));
					else mover(Movimiento(Posicion(7, movimiento.inicio.y), Posicion(5, movimiento.inicio.y)));

					infoTablas.clear();
				}
			}

			actualizarHaMovido(movimiento);

			jugadaHecha = true;
			break;
		}
	}


	if (jugadaHecha)
	{
		if (leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::PEON && movimiento.fin.y % 7 == 0)
		{
			Pieza* p_peon = leer(movimiento.inicio);
			coronar(movimiento.inicio, MotorDeJuego::seleccionarEntradaCoronar(movimiento, *this, interaccion));
			delete p_peon;

			infoTablas.clear();
		}

		cambiarTurno();
		ultimaJugada = movimiento;
		mover(movimiento);

		return true;
	}

	return false;
}

void Tablero::coronar(Posicion posicion, Pieza::tipo_t tipo)
{
	switch (tipo)
	{
	case Pieza::tipo_t::CABALLO:
		escribir(posicion, new Caballo(*this, leer(posicion)->getColor()));
		break;
	case Pieza::tipo_t::ALFIL:
		escribir(posicion, new Alfil(*this, leer(posicion)->getColor()));
		break;
	case Pieza::tipo_t::TORRE:
		escribir(posicion, new Torre(*this, leer(posicion)->getColor()));
		break;
	case Pieza::tipo_t::DAMA:
		escribir(posicion, new Dama(*this, leer(posicion)->getColor()));
		break;
	}
}

bool Tablero::jaqueMate() const 
{
	if (leer(reyPos[colorDelTurno])->getAmenazas().size() == 0)
	{
		return false;
	}
	else
	{
		if (leer(reyPos[colorDelTurno])->getAmenazas().size() > 1)
		{
			//Comprobar si el rey puede mover
			if (leer(reyPos[colorDelTurno])->getPuedeMover().size() > 0 || leer(reyPos[colorDelTurno])->getPuedeComer().size() > 0)
				return false;
			//Si no jaque mate
			return true;
		}
		else
		{
			if (leer(reyPos[colorDelTurno])->getAmenazas()[0]->tipo == Pieza::tipo_t::CABALLO || distancia(leer(reyPos[colorDelTurno])->getAmenazas()[0]->posicion, leer(reyPos[colorDelTurno])->posicion) < 2.0)
			{
				//Comprobar si el rey puede mover 
				if (leer(reyPos[colorDelTurno])->getPuedeMover().size() > 0 || leer(reyPos[colorDelTurno])->getPuedeComer().size() > 0)
					return false;

				//Comprobar si se puede comer el caballo
				if (leer(reyPos[colorDelTurno])->getAmenazas()[0]->getAmenazas().size() > 0)
				{
					for (auto comprobarAmenazas : leer(reyPos[colorDelTurno])->getAmenazas()[0]->getAmenazas())
					{
						for (auto hayAmenaza : comprobarAmenazas->getPuedeComer())
						{
							if (hayAmenaza == leer(reyPos[colorDelTurno])->getAmenazas()[0])
								return false;
						}
					}
				}
					

				//Si ninguna jaque mate
				return true;

			}
			else
			{
				//Comprobar si el rey puede mover (si no puede entonces jaque mate)
				if (leer(reyPos[colorDelTurno])->getPuedeMover().size() > 0 || leer(reyPos[colorDelTurno])->getPuedeComer().size() > 0)
					return false;

				//Comprobar si se puede comer la pieza
				if (leer(reyPos[colorDelTurno])->getAmenazas()[0]->getAmenazas().size() > 0)
				{
					for (auto comprobarAmenazas : leer(reyPos[colorDelTurno])->getAmenazas()[0]->getAmenazas())
					{
						for (auto hayAmenaza : comprobarAmenazas->getPuedeComer())
						{
							if (hayAmenaza == leer(reyPos[colorDelTurno])->getAmenazas()[0])
								return false;
						}
					}
				}

				//Comprobar si se puede poner algo en medio
				std::vector<DatosBloqueoJaque> Bloquea = bloqueoJaque();
				if(Bloquea.size()>0)

					return false;

				//Si ninguna jaque mate
				return true;
			}
		}
	}
	
}



bool Tablero::reyAhogado() const // como se llama al jaque mate antes no es necesario revisar si el rey tiene amenazas.
{
	for (auto piezasColor : tablero)
	{
		if (piezasColor != nullptr && piezasColor->color == colorDelTurno) {
			if (leer(piezasColor->posicion)->puede_comer.size() > 0 || leer(piezasColor->posicion)->puede_mover.size() > 0)
				return false;
		}
	}
	
	return true;
}

bool Tablero::tablasMaterialInsuficiente() const {
	bool colorPrueba;
	bool PrimerAlfil=false;
	int ColorAlfil;

	if (numeroPiezas == 2) //Comprobar si solo quedan los reyes
	{
		return true;
	}

	if (numeroPiezas <= 4) {
		for (auto piezasPrueba : tablero)
		{
			if (piezasPrueba != nullptr)
			{
				if (numeroPiezas == 3) //Comprobar si es Caballo + Rey o Alfil + Rey vs Rey
				{
					if (piezasPrueba->tipo == Pieza::tipo_t::CABALLO || piezasPrueba->tipo == Pieza::tipo_t::ALFIL)
						return true;
				}
				else //Comprobar si uno tiene 1 alfil de un color y el rival el de color contrario
				{
					if (piezasPrueba->tipo == Pieza::tipo_t::ALFIL)
					{
						if (!PrimerAlfil) {
							colorPrueba=piezasPrueba->color;
							PrimerAlfil = true;
							ColorAlfil = piezasPrueba->posicion.x % 2+ piezasPrueba->posicion.y % 2; //Todas las casillas o son par/impar o par/par impar/impar
						}
						else
						{
							if (piezasPrueba->color == colorPrueba)
							{
								return false;
							}
							else
							{

								if ((piezasPrueba->posicion.x%2 + piezasPrueba->posicion.y % 2) == ColorAlfil)
								{
									return true;
								}
								else
								{
									return false;
								}
							}
						}
					}	
				}
			}
		}
	}

	return false;
}

void Tablero::actualizarHaMovido(Movimiento movimiento)
{
	if (leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::TORRE && !haMovido[leer(movimiento.inicio)->color * 3 + movimiento.inicio.x / 7 + 1] &&
		movimiento.inicio.y == !leer(movimiento.inicio)->color * 7) haMovido[leer(movimiento.inicio)->color * 3 + movimiento.inicio.x / 7 + 1] = true;

	else if (leer(movimiento.inicio)->getTipo() == Pieza::tipo_t::REY && !haMovido[leer(movimiento.inicio)->color * 3])
		haMovido[leer(movimiento.inicio)->color * 3] = true;

	if (leer(movimiento.fin) != nullptr && leer(movimiento.fin)->getTipo() == Pieza::tipo_t::TORRE && movimiento.fin.y == !leer(movimiento.fin)->color * 7) 
		haMovido[leer(movimiento.fin)->color * 3 + movimiento.inicio.x / 4 + 1] = true;
}

void Tablero::actualizarEnroque()
{
	if (!haMovido[colorDelTurno * 3] && leer(reyPos[colorDelTurno])->getAmenazas().size() == 0)
	{
		// Enroque largo
		if (!haMovido[1 + colorDelTurno * 3] && leer(reyPos[colorDelTurno] - Posicion(1, 0)) == nullptr && leer(reyPos[colorDelTurno] - Posicion(2, 0)) == nullptr &&
			!tableroIlegalesRey[colorDelTurno][reyPos[colorDelTurno].x - 1][reyPos[colorDelTurno].y] && !tableroIlegalesRey[colorDelTurno][reyPos[colorDelTurno].x - 2][reyPos[colorDelTurno].y])
			tablero[reyPos[colorDelTurno].indice()]->puede_mover.push_back(reyPos[colorDelTurno] - Posicion(2, 0));

		// Enroque corto
		if (!haMovido[2 + colorDelTurno * 3] && leer(reyPos[colorDelTurno] + Posicion(1, 0)) == nullptr && leer(reyPos[colorDelTurno] + Posicion(2, 0)) == nullptr &&
			!tableroIlegalesRey[colorDelTurno][reyPos[colorDelTurno].x + 1][reyPos[colorDelTurno].y] && !tableroIlegalesRey[colorDelTurno][reyPos[colorDelTurno].x + 2][reyPos[colorDelTurno].y])
			tablero[reyPos[colorDelTurno].indice()]->puede_mover.push_back(reyPos[colorDelTurno] + Posicion(2, 0));
	}
}

std::vector<DatosBloqueoJaque> Tablero::bloqueoJaque() const
{
	std::vector<DatosBloqueoJaque> piezasBloquean;
	Posicion direccion,posicionPrueba;
	int restaX = (leer(reyPos[colorDelTurno])->posicion - leer(reyPos[colorDelTurno])->amenazas[0]->posicion).x;
	int restaY = (leer(reyPos[colorDelTurno])->posicion - leer(reyPos[colorDelTurno])->amenazas[0]->posicion).y;

	int distan =  std::max(abs(restaX),abs(restaY));

	direccion.x = round(restaX / (float)distan);
	direccion.y = round(restaY / (float)distan);

	

	DatosBloqueoJaque aux;

	for (auto piezasMueven : tablero)
	{
		if (piezasMueven != nullptr&&piezasMueven->color==colorDelTurno)
		{
			for (auto testPosiciones : piezasMueven->getPuedeMover())
			{
				for (int i = 1; i < distan; i++)
				{
					posicionPrueba = leer(reyPos[colorDelTurno])->amenazas[0]->posicion + direccion * i;
					if (testPosiciones == posicionPrueba)
					{
						aux.datosPieza = piezasMueven;
						aux.posicionPieza = posicionPrueba;
						piezasBloquean.push_back(aux);
					}
				}
			}
		}
	}


	return piezasBloquean;
}

void Tablero::actualizarJaque() {
	if (leer(reyPos[colorDelTurno])->getAmenazas().size() > 0)
	{
		std::vector<DatosBloqueoJaque> Bloquea;
		if (leer(reyPos[colorDelTurno])->getAmenazas()[0]->tipo != Pieza::tipo_t::CABALLO && distancia(leer(reyPos[colorDelTurno])->getAmenazas()[0]->posicion, leer(reyPos[colorDelTurno])->posicion) >= 2.0)
		{
			Bloquea = bloqueoJaque();
		}

		for (auto borrarMov : tablero)
		{
			if (borrarMov != nullptr && borrarMov->color == colorDelTurno && borrarMov->tipo != Pieza::tipo_t::REY)
			{
				borrarMov->clearVariables();
			}
		}

		if (leer(reyPos[colorDelTurno])->getAmenazas().size() ==1)//Si se puede solventar el jaque con una pieza que no sea el rey
		{
			for (auto Amenazas : leer(reyPos[colorDelTurno])->getAmenazas()[0]->getAmenazas()) //Si se puede comer la pieza se actualizan para que las piezas puedan comersela
			{
				if (Amenazas->tipo != Pieza::tipo_t::REY || tableroIlegalesRey[colorDelTurno][leer(reyPos[colorDelTurno])->getAmenazas()[0]->getPosicion().x][leer(reyPos[colorDelTurno])->getAmenazas()[0]->getPosicion().y] == false)
				{
					Amenazas->puede_comer.push_back(leer(reyPos[colorDelTurno])->getAmenazas()[0]);

					for (int i = 0; i < datosClavada.size();i++)
					{
						if (datosClavada[i].PiezaClavada == Amenazas)
						{
							Amenazas->puede_comer.clear();
						}
					}
				}
				
			}

			//Comprobar si se puede poner algo en medio
			for (auto Bloqueos : Bloquea)
			{
				Bloqueos.datosPieza->puede_mover.push_back(Bloqueos.posicionPieza);
			}
			
		}
	}
}

void Tablero::actualizarAlPaso() 
{
	int alturaInicial[2] = { 6,1 };
	int alturaFinal[2] = { 4,3 };

	if (leer(ultimaJugada.fin)!=nullptr&&
		leer(ultimaJugada.fin)->tipo == Pieza::tipo_t::PEON
		&& ultimaJugada.inicio.y == alturaInicial[leer(ultimaJugada.fin)->color] 
		&& ultimaJugada.fin.y == alturaFinal[leer(ultimaJugada.fin)->color])
	{
		Posicion posicionPosible[2] = { Posicion{ultimaJugada.fin - Posicion{1,0}},Posicion{ultimaJugada.fin + Posicion{1,0}} };
		for (int i=0;i<2;i++)
		{
			if (posicionPosible[i]>= Posicion(0, 0) && posicionPosible[i]< Posicion(8, 8) &&leer(posicionPosible[i]) != nullptr && leer(posicionPosible[i])->tipo == Pieza::tipo_t::PEON)
			{
				leer(posicionPosible[i])->puede_comer.push_back(leer(ultimaJugada.fin));
				Posicion jugadaIntermedia = ultimaJugada.fin + ultimaJugada.inicio;
				jugadaIntermedia.x /= 2;
				jugadaIntermedia.y /= 2;
				leer(posicionPosible[i])->puede_mover.push_back(jugadaIntermedia);
				leer(ultimaJugada.fin)->amenazas.push_back(leer(posicionPosible[i]));
			}
		}
	}
}