#include "Tablero.h"
#include "Caballo.h"
#include "Rey.h"
#include "Peon.h"
#include "Alfil.h"
#include "Torre.h"
#include "Dama.h"
#include <iostream>
#include <string>
#include <cmath>

//constexpr auto NUM_LINEAS = 40;
constexpr auto COEFF_DIFERENCIA_MATERIAL = 50.0;
constexpr auto COEFF_AMENAZAS_PELIGROSAS = 40.0;
constexpr auto COEFF_AMENAZAS_POCO_PELIGROSAS = 10.0;
constexpr auto VALOR_AMENAZAS_PELIGROSAS = 1.79769e+308;

void Tablero::actualizarTablero()
{
	for (auto limpiezaAmenazas : tablero) {
		if (limpiezaAmenazas!=nullptr)
			limpiezaAmenazas->amenazas.clear();
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
			aux=p_pieza->actualizarVariables(false,Posicion{0,0}, tableroIlegalesRey);
			if (aux.ExisteClavada == true)
			{
				datosClavada.push_back(aux);
			}
		}
	}
	for (int i = 0; i < datosClavada.size(); i++) //Clavar las piezas clavadas
	{
		datosClavada[i].PiezaClavada->actualizarVariables(true, datosClavada[i].DireccionClavada,tableroIlegalesRey);
	}	

	actualizarEnroque();

}

Tablero::Tablero()
{
	for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++) { tablero[i] = nullptr; } //Se crea un tablero vacio
	
	//True == Blancas <-> False == Negras En color
	//Blancas 
	//Se añaden los peones
	/*for (int i = 0; i < ANCHO_TABLERO; i++)
	{
		escribir(Posicion(i, 1), new Peon(*this, true));
	}*/

	////Se añaden las torres
	escribir(Posicion(0, 0), new Torre(*this, true));
	escribir(Posicion(7, 0), new Torre(*this, true));

	////Se escriben los caballos
	//escribir(Posicion(1, 0), new Caballo(*this, true));
	//escribir(Posicion(6, 0), new Caballo(*this, true));

	////Se escriben los alfiles
	escribir(Posicion(2, 0), new Alfil(*this, true));
	escribir(Posicion(5, 0), new Alfil(*this, true));

	////Se escribe la dama y el rey
	//escribir(Posicion(3, 0), new Dama(*this, true));
	escribir(Posicion(4, 0), new Rey(*this, true));
	reyPos[1] = Posicion{ 4,0 };

	////Negras
	////Se añaden los peones
	//for (int i = 0; i < ANCHO_TABLERO; i++)
	//{
	//	escribir(Posicion(i, 6), new Peon(*this, false));
	//}
	////Se añaden las torres
	escribir(Posicion(0, 7), new Torre(*this, false));
	escribir(Posicion(7, 7), new Torre(*this, false));

	////Se escriben los caballos
	//escribir(Posicion(1, 7), new Caballo(*this, false));
	//escribir(Posicion(6, 7), new Caballo(*this, false));

	////Se escriben los alfiles
	//escribir(Posicion(2, 7), new Alfil(*this, false));
	//escribir(Posicion(5, 7), new Alfil(*this, false));

	////Se escribe la dama y el rey
	//escribir(Posicion(3, 7), new Dama(*this, false));
	escribir(Posicion(4, 7), new Rey(*this, false));
	reyPos[0] = Posicion{ 4,7 };

	actualizarTablero(); //Se inicializan los movimientos posibles
	numeroPiezas = 32;
	
	actualizarTablero();
	colorDelTurno = true;
}

Tablero::Tablero(const Tablero& tablero)
{
	for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++)
	{
		if (tablero.tablero[i] != nullptr)
		{
			switch (tablero.tablero[i]->tipo)
			{
			case Pieza::tipo_t::PEON:
				escribir(tablero.posicion(i), new Peon(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::CABALLO:
				escribir(tablero.posicion(i), new Caballo(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::ALFIL:
				escribir(tablero.posicion(i), new Alfil(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::TORRE:
				escribir(tablero.posicion(i), new Torre(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::DAMA:
				escribir(tablero.posicion(i), new Dama(*this, tablero.tablero[i]->color));
				break;
			case Pieza::tipo_t::REY:
				escribir(tablero.posicion(i), new Rey(*this, tablero.tablero[i]->color));
				break;
			}
		}
		else this->tablero[i] = nullptr;
	}
	//Copiar resto de variables
	this->numeroPiezas = tablero.numeroPiezas;
	this->colorDelTurno = tablero.colorDelTurno;
	this->reyPos[0] = tablero.reyPos[0];
	this->reyPos[1] = tablero.reyPos[1];

}

Tablero::~Tablero()
{
	for (Pieza* p_pieza : tablero) delete p_pieza;
}

void Tablero::escribir(const Posicion& posicion, Pieza* pieza)
{
	tablero[posicion.x + posicion.y * ANCHO_TABLERO] = pieza;
	if (pieza != nullptr) pieza->posicion = posicion;
}

void Tablero::mover(const Movimiento& movimiento) {
	escribir(movimiento.fin, leer(movimiento.inicio));
	escribir(movimiento.inicio, nullptr);

	if (leer(movimiento.fin)->tipo == Pieza::tipo_t::REY)
	{
		reyPos[leer(movimiento.fin)->color] = movimiento.fin; // Si se mueve un rey acctualizar la variable reyPos
	}

	actualizarTablero();
}

bool Tablero::jaqueMate() const 
{
	if (leer(reyPos[colorDelTurno])->getAmenazas().size() == 0)
	{
		return false;
	}
	else
	{
		if (leer(reyPos[colorDelTurno])->getAmenazas().size()> 1)
		{
			//Comprobar si el rey puede mover
			if (leer(reyPos[colorDelTurno])->getPuedeMover().size() > 0 || leer(reyPos[colorDelTurno])->getPuedeComer().size() > 0)
				return false;
			//Si no jaque mate
			return true;
		}
		else
		{
			if (leer(reyPos[colorDelTurno])->getAmenazas()[0]->tipo == Pieza::tipo_t::CABALLO|| distancia(leer(reyPos[colorDelTurno])->getAmenazas()[0]->posicion, leer(reyPos[colorDelTurno])->posicion)<2.0)
			{
				//Comprobar si el rey puede mover 
				if (leer(reyPos[colorDelTurno])->getPuedeMover().size() > 0 || leer(reyPos[colorDelTurno])->getPuedeComer().size() > 0)
					return false;

				//Comprobar si se puede comer el caballo
				if (leer(reyPos[colorDelTurno])->getAmenazas()[0]->getAmenazas().size() > 0)
					return false;

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
					return false;

				//Comprobar si se puede poner algo en medio
				std::vector<Pieza*> Bloquea = bloqueoJaque();
				if(Bloquea.size()>0);
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
	bool aux = !this->colorDelTurno;
	if (!haMovido[aux * 3]/* && !rey en jaque*/)
	{
		// Enroque largo
		if (!haMovido[1 + aux * 3] && leer(reyPos[aux] - Posicion(1, 0)) == nullptr && leer(reyPos[aux] - Posicion(2, 0)) == nullptr &&
			!tableroIlegalesRey[aux][reyPos[aux].x - 1][reyPos[aux].y] && !tableroIlegalesRey[aux][reyPos[aux].x - 2][reyPos[aux].y])
			tablero[reyPos[aux].indice()]->puede_mover.push_back(reyPos[aux] - Posicion(2, 0));
		
		// Enroque corto
		if (!haMovido[2 + aux * 3] && leer(reyPos[aux] + Posicion(1, 0)) == nullptr && leer(reyPos[aux] + Posicion(2, 0)) == nullptr &&
			!tableroIlegalesRey[aux][reyPos[aux].x + 1][reyPos[aux].y] && !tableroIlegalesRey[aux][reyPos[aux].x + 2][reyPos[aux].y])
			tablero[reyPos[aux].indice()]->puede_mover.push_back(reyPos[aux] + Posicion(2, 0));	
	}
}

double Tablero::evaluacion() const  //Valor negativo ventaja negras valor positivo ventaja blancas
{
	double amenazaPeligrosa = VALOR_AMENAZAS_PELIGROSAS; //Valor para luego comparar si hay amenazas de piezas de menor a piezas de mayor valor (se pone a un valor de error)
	double amenazaPocoPeligrosa = 0;		//Valor para registrar valor de amenazas de mayor valor a una pieza de menor valor
	double proteccion = 0;					//Valor de piezas que defienden de una amenaza poco peligrosa
	double valorTablero = 0;

	//Para llevar la cuenta
	double amenazaPeligrosaReturn = 0;
	double amenazaPocoPeligrosaReturn = 0;

	for (auto piezaAnalizada : tablero) 
	{

		//Se reinicializan los valores en cada ciclo
		amenazaPeligrosa = VALOR_AMENAZAS_PELIGROSAS;
		amenazaPocoPeligrosa = 0;
		proteccion = 0;


		valorTablero += pow(-1, 1+piezaAnalizada->color) * piezaAnalizada->value; //Resta si es negra y suma si es blanca

		for (auto piezasAmenazasAPiezaAnalizada : piezaAnalizada->getAmenazas())
		{
			if (piezaAnalizada->value - piezasAmenazasAPiezaAnalizada->value > 1) //Si la amenaza es peligrosa pieza de menor valor amenaza una de mayor valor
			{
				if (amenazaPeligrosa > abs(piezaAnalizada->value - piezasAmenazasAPiezaAnalizada->value)) //Se mete la pieza de menor valor que amenenaza a la de mayor valor
					amenazaPeligrosa = pow(-1,piezaAnalizada->color) * abs(piezaAnalizada->value - piezasAmenazasAPiezaAnalizada->value); //Valor con signo para suma final
			}
			else
			{
				amenazaPocoPeligrosa += piezasAmenazasAPiezaAnalizada->value; //Valor sin signo temporal
			}
		}
		for (auto piezasDefiendenAPiezaAnalizada : piezaAnalizada->EstaProtegida())
		{
			proteccion += piezasDefiendenAPiezaAnalizada->value; //Valor sin signo temporal
		}

		if (amenazaPeligrosa != VALOR_AMENAZAS_PELIGROSAS)
		{
			amenazaPeligrosaReturn += amenazaPeligrosa;
		}
			
		amenazaPocoPeligrosaReturn += pow(-1,piezaAnalizada->color) * piezaAnalizada->value*abs(proteccion / piezaAnalizada->EstaProtegida().size()- amenazaPocoPeligrosa / piezaAnalizada->getAmenazas().size() );
	}

	return COEFF_DIFERENCIA_MATERIAL*valorTablero+COEFF_AMENAZAS_PELIGROSAS* amenazaPeligrosaReturn +COEFF_AMENAZAS_POCO_PELIGROSAS* amenazaPeligrosaReturn;
}

std::vector<Pieza*> Tablero::bloqueoJaque() const {
	Posicion direccion,posicionPrueba;
	int distan = static_cast<int> (distancia(leer(reyPos[colorDelTurno])->posicion, leer(reyPos[colorDelTurno])->amenazas[0]->posicion));
	direccion.x = (leer(reyPos[colorDelTurno])->posicion - leer(reyPos[colorDelTurno])->amenazas[0]->posicion).x / distan;
	direccion.y = (leer(reyPos[colorDelTurno])->posicion - leer(reyPos[colorDelTurno])->amenazas[0]->posicion).y / distan;


	std::vector<Pieza*> piezasBloquean;
	for (int i = 1; i < distan; i++)
	{
		posicionPrueba = leer(reyPos[colorDelTurno])->amenazas[0]->posicion + Posicion{ i * direccion.x,i * direccion.y };
		for (auto piezasMueven : tablero)
		{
			if (piezasMueven != nullptr&&piezasMueven->color==colorDelTurno)
			{
				for (auto testPosiciones : piezasMueven->getPuedeMover())
				{
					if (testPosiciones == posicionPrueba)
					{
						piezasBloquean.push_back(piezasMueven);
					}
						
				}
			}
			
		}
	}	
	return piezasBloquean;
}

bool Tablero::actualizarJaque() {
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
					return false;

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
					return false;

				//Comprobar si se puede poner algo en medio
				std::vector<Pieza*> Bloquea = bloqueoJaque();
				if (Bloquea.size() > 0);
				return false;

				//Si ninguna jaque mate
				return true;
			}
		}
	}
}