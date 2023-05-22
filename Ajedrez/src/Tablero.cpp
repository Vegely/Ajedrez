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


constexpr auto NUM_LINEAS = 40;
constexpr auto COEFF_DIFERENCIA_MATERIAL = 50.0;
constexpr auto COEFF_AMENAZAS_PELIGROSAS = 40.0;
constexpr auto COEFF_AMENAZAS_POCO_PELIGROSAS = 10.0;
constexpr auto VALOR_AMENAZAS_PELIGROSAS = 1.79769e+308;

void Tablero::actualizarTablero()
{
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
}

Tablero::Tablero()
{
	for (int i = 0; i < ANCHO_TABLERO * ANCHO_TABLERO; i++) { tablero[i] = nullptr; } //Se crea un tablero vacio

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
	escribir(Posicion(3, 0), new Dama(*this, true));
	escribir(Posicion(4, 0), new Rey(*this, true));
	ReyPos[1] = Posicion{4,0};

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

	//Se escribe la dama y el rey
	escribir(Posicion(3, 7), new Dama(*this, false));
	escribir(Posicion(4, 7), new Rey(*this, false));
	ReyPos[0] = Posicion{ 4,7 };

	actualizarTablero(); //Se inicializan los movimientos posibles
	numeroPiezas = 32;
	ColorDelTurno=true;

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
	this->ColorDelTurno = tablero.ColorDelTurno;
	this->ReyPos[0] = tablero.ReyPos[0];
	this->ReyPos[1] = tablero.ReyPos[1];

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

bool Tablero::mover(const Movimiento& movimiento) {
	if (leer(movimiento.inicio) != nullptr && leer(movimiento.inicio)->color == ColorDelTurno)		//Si no hay pieza en p1 no se puede mover
	{
		if (leer(movimiento.fin) == nullptr)	//Si no hay pieza en p2 si se puede mover se mueve
		{
			for (const Posicion puedeMover : leer(movimiento.inicio)->getPuedeMover())
			{
				if (puedeMover == movimiento.fin)
				{
					escribir(movimiento.fin, leer(movimiento.inicio));
					escribir(movimiento.inicio, nullptr);
					actualizarTablero();

					if (leer(ReyPos[ColorDelTurno])->amenazas.size() > 0) //Si al mover pones el rey en jaque deshaces el movimiento
					{
						escribir(movimiento.inicio, leer(movimiento.fin));
						escribir(movimiento.fin, nullptr);
						actualizarTablero();
						return false;
					}
						
					if (leer(movimiento.fin)->tipo == Pieza::tipo_t::REY)
					{
						ReyPos[leer(movimiento.inicio)->color] = movimiento.fin;
						
					}

					return true;					
				}
			}
		}
		else
		{
			for (const Pieza* puedeComer:leer(movimiento.inicio)->getPuedeComer())
			{
				if (puedeComer == leer(movimiento.fin))
				{
					Pieza* p_piezaComida = leer(movimiento.fin);

					escribir(movimiento.fin, leer(movimiento.inicio));
					escribir(movimiento.inicio, nullptr);
					actualizarTablero();

					if (leer(ReyPos[ColorDelTurno])->amenazas.size() > 0) //Si al mover pones el rey en jaque deshaces el movimiento
					{
						escribir(movimiento.inicio, leer(movimiento.fin));
						escribir(movimiento.fin, p_piezaComida);
						actualizarTablero();
						return false;
					}

					if (leer(movimiento.fin)->tipo == Pieza::tipo_t::REY)
					{
						ReyPos[leer(movimiento.inicio)->color] = movimiento.fin;
					}

					numeroPiezas--;
					return true;
				}
			}
		}
	}
	
	return false;
}




bool Tablero::jaqueMate() const 
{
	if (leer(ReyPos[ColorDelTurno]) != nullptr )
	{
		if (leer(ReyPos[ColorDelTurno])->getAmenazas().size() == 0)
		{
			return false;
		}
		else
		{
			if (leer(ReyPos[ColorDelTurno])->getAmenazas().size()> 1)
			{
				//Comprobar si el rey puede mover


				//Si no jaque mate
			}
			else
			{
				if (leer(ReyPos[ColorDelTurno])->getAmenazas()[0]->tipo == Pieza::tipo_t::CABALLO|| distancia(leer(ReyPos[ColorDelTurno])->getAmenazas()[0]->posicion, leer(ReyPos[ColorDelTurno])->posicion)<2.0)
				{
					//Comprobar si el rey puede mover 
					//Comprobar si se puede comer el caballo

					//Si ninguna jaque mate

				}
				else
				{

					//Comprobar si el rey puede mover (si no puede entonces jaque mate)
					//Comprobar si se puede comer la pieza
					//Comprobar si se puede poner algo en medio

					//Si ninguna jaque mate
				}
			}
		}
	}
	return false;
}

bool Tablero::reyAhogado() const {
	for (auto piezasColor : tablero)
	{
		if (piezasColor != nullptr && piezasColor->color == ColorDelTurno) {

		}

	}
	return false;

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

//////////////////////////////////////////////////////////////////////////////
void Tablero::imprimeTablero() {
	//Insertar lineas vacias para limpiar consola
	for (int i = 0; i < NUM_LINEAS; i++) {
		std::cout << std::endl << std::endl;
	}
	
	// Pintar el tablero
	int i = 0;
	for (Pieza* p_pieza : tablero)
	{
		if (p_pieza == nullptr) std::cout << "---\t";
		else std::cout << p_pieza->getNombre() << " " << p_pieza->color << "\t";

		if (i++ % 8 == 7) std::cout << "\n\n";
	}
}
//////////////////////////////////////////////////////////////////////////////


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
