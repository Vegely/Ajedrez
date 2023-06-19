#pragma once

#include "Tablero.h"
#include "Mundo.h"
#include "IA.h";
#include "ConfiguracionDeJuego.h"

#include "ElementoRed.h"

enum class CodigoFinal { JAQUE_MATE, REY_AHOGADO, TABLAS_POR_MATERIAL_INSUFICIENTE, TABLAS_POR_REPETICION, TABLAS_POR_PASIVIDAD };	

struct DatosFinal
{
	CodigoFinal codigoFinal;
	bool ganaBlanco;
};

class MotorDeJuego
{
	const ConfiguracionDeJuego config;
	Tablero tablero;

	Movimiento seleccionarEntrada(Mundo* p_motorGrafico);
	Movimiento ensamblarMovimiento(Posicion posicion, Mundo* p_motorGrafico) const;

public:
	MotorDeJuego(const ConfiguracionDeJuego& config) : config(config), tablero(Tablero(true)) { /*pintar();*/ }

	Tablero* getTablero(void) { return &this->tablero; }
	void liberar() { tablero.liberar(); }
	void pintar(const Posicion& posSelec, Mundo* p_motorGrafico) const;

	static Pieza::tipo_t seleccionarEntradaCoronar(const Movimiento& movimiento, const Tablero& tablero, const ConfiguracionDeJuego::FormasDeInteraccion& interaccion, Mundo* motorGrafico);

	DatosFinal motor(Mundo* mundoGrafico);
};

