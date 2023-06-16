#pragma once

#include "Tablero.h"
#include "Mundo.h"
#include "IA.h";
#include "ConfiguracionDeJuego.h"

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

	Movimiento seleccionarEntrada(Mundo* p_motorGrafico, bool pos1Selec);
	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec) const;
	bool hacerJugada(Movimiento movimiento, Mundo* motorGrafico);

	static Pieza::tipo_t seleccionarEntradaCoronar(const Movimiento& movimiento, const Tablero& tablero, const ConfiguracionDeJuego::FormasDeInteraccion& interaccion, Mundo* motorGrafico);

public:
	MotorDeJuego(const ConfiguracionDeJuego& config) : config(config), tablero(Tablero(true)) { /*pintar()*/; }
	Tablero* getTablero(void) { return &this->tablero; }
	void liberar() { tablero.liberar(); }

	DatosFinal motor(Mundo* mundoGrafico);
};

