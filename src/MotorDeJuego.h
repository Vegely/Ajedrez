#ifndef _MOTORDEJUEGO__H_
#define _MOTORDEJUEGO__H_

#include "Tablero.h"
#include "Mundo.h"
#include "IA.h";
#include "ConfiguracionDeJuego.h"
#include "Partida.h"

#include "ElementoRed.h"

enum class CodigoFinal { JAQUE_MATE, REY_AHOGADO, TABLAS_POR_MATERIAL_INSUFICIENTE, TABLAS_POR_REPETICION, TABLAS_POR_PASIVIDAD };	

struct DatosFinal
{
	CodigoFinal codigoFinal;
	bool finalizada = false;
	bool ganaBlanco;
};

class MotorDeJuego
{
	Partida& fichero_partida;

	const ConfiguracionDeJuego config;
	ElementoRed& elementoRed;

	Tablero tablero;
	//bool exit = false;

	Movimiento seleccionarEntrada(Mundo* p_motorGrafico, bool& run);
	Movimiento ensamblarMovimiento(Posicion posicion) const;

public:
	friend class IA;

	MotorDeJuego(const ConfiguracionDeJuego* config, Partida* partida, ElementoRed* elementoRed) : config(*config), tablero(Tablero(true)), fichero_partida(*partida), elementoRed(*elementoRed) { /*pintar();*/ }

	//Tablero* getTablero(void) { return &this->tablero; }
	void liberar() { tablero.liberar(); }
	void pintarSeleccionCasilla(const Posicion& posSelec, Mundo* p_motorGrafico) const;

	static Pieza::tipo_t seleccionarEntradaCoronar(MotorDeJuego& motor, const Movimiento& movimiento, const Tablero& tablero, const ConfiguracionDeJuego::FormasDeInteraccion& interaccion, Mundo* motorGrafico, bool& run, bool guardarCoronacion);

	//void setExit(bool exit) { this->exit = exit; }

	DatosFinal motor(Mundo* mundoGrafico, bool& run);
};

#endif // !_MOTORDEJUEGO__H_