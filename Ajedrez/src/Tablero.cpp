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
constexpr auto COEFF_DIFERENCIA_MATERIAL = 0.0;
constexpr auto COEFF_AMENAZAS_PELIGROSAS = 0.0;
constexpr auto COEFF_AMENAZAS_POCO_PELIGROSAS = 0.0;
constexpr auto VALOR_AMENAZAS_PELIGROSAS = 1.79769e+308;

void Tablero::actualizarTablero()
{
	for (Pieza* p_pieza : tablero) if (p_pieza != nullptr) p_pieza->actualizarVariables();
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

	actualizarTablero(); //Se inicializan los movimientos posibles
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

					if (!jaqueMate())
					{
						cambiarTurno();
						return true;
					}
					
					escribir(movimiento.inicio, leer(movimiento.fin));
					escribir(movimiento.fin, nullptr);
					actualizarTablero();
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

					if (!jaqueMate())
					{
						delete p_piezaComida; //Liberar espacio de memoria de la pieza comida
						
						cambiarTurno();
						return true;
					}

					escribir(movimiento.inicio, leer(movimiento.fin));
					escribir(movimiento.fin, p_piezaComida);
					actualizarTablero();
				}
			}
		}
	}
	
	return false;
}

bool Tablero::jaqueMate() const 
{ 
	for (Pieza* p_pieza : tablero) if (p_pieza != nullptr && p_pieza->tipo == Pieza::tipo_t::REY && p_pieza->getAmenazas().size() == 0) return false;
	return true;
}

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

double Tablero::evaluacion() const  //Valor negativo ventaja negras valor positivo ventaja blancas
{
	double valorTablero = 0;
	double amenaza_peligrosa = 1.79769e+308; //Valor para luego comparar si hay amenazas de piezas de menor a piezas de mayor valor (se pone a un valor de error)
	double amenaza_poco_peligrosa = 0;		//Valor para registrar valor de amenazas de mayor valor a una pieza de menor valor
	double proteccion = 0;					//Valor de piezas que defienden de una amenaza poco peligrosa
	double amenaza_poco_peligrosa = 0;
	double amenaza_peligrosa_return = 0;
	double amenaza_poco_peligrosa_return = 0;

	for (auto pieza_analizada : tablero) 
	{
		valorTablero += pow(-1, 1+pieza_analizada->color) * pieza_analizada->value; //Resta si es negra y suma si es blanca

		//Se reinicializan los valores en cada ciclo
		amenaza_peligrosa = VALOR_AMENAZAS_PELIGROSAS;
		amenaza_poco_peligrosa = 0;		
		proteccion = 0;					
		amenaza_poco_peligrosa = 0;

		for (auto piezas_amenazanA : pieza_analizada->getAmenazas())
		{
			if (pieza_analizada->value - piezas_amenazanA->value > 1) //Si la amenaza es peligrosa pieza de menor valor amenaza una de mayor valor
			{
				if (amenaza_peligrosa > abs(pieza_analizada->value - piezas_amenazanA->value))
					amenaza_peligrosa = pow(-1, 1 + pieza_analizada->color) * abs(pieza_analizada->value - piezas_amenazanA->value); //Valor con signo para suma final
			}
			else
			{
				amenaza_poco_peligrosa += piezas_amenazanA->value; //Valor sin signo temporal
			}
		}
		for (auto piezas_defiendenA : pieza_analizada->EstaProtegida())
		{
			proteccion += piezas_defiendenA->value; //Valor sin signo temporal
		}

		if (amenaza_peligrosa != VALOR_AMENAZAS_PELIGROSAS)
		{
			amenaza_peligrosa_return += amenaza_peligrosa;
		}
			


		amenaza_poco_peligrosa_return += pow(-1, 1 + pieza_analizada->color) * abs(pieza_analizada->value - amenaza_poco_peligrosa / pieza_analizada->getAmenazas().size() - proteccion / pieza_analizada->EstaProtegida().size());
	}

	return COEFF_DIFERENCIA_MATERIAL*valorTablero+COEFF_AMENAZAS_PELIGROSAS* amenaza_peligrosa_return +COEFF_AMENAZAS_POCO_PELIGROSAS* amenaza_peligrosa_return;
}