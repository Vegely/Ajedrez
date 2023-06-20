#pragma once

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
	bool ganaBlanco;
	bool finalizada = false;
};

class MotorDeJuego
{
	Partida* fichero_partida = nullptr;
	const ConfiguracionDeJuego config;
	Tablero tablero;
	bool exit = false;

	Movimiento seleccionarEntrada(Mundo* p_motorGrafico);
	Movimiento ensamblarMovimiento(Posicion posicion, Mundo* p_motorGrafico) const;

public:
	MotorDeJuego(const ConfiguracionDeJuego& config, Partida* partida = nullptr) : config(config), tablero(Tablero(true)), fichero_partida(partida) { /*pintar();*/ }

	Tablero* getTablero(void) { return &this->tablero; }
	void liberar() { tablero.liberar(); }
	void pintarSeleccionCasilla(const Posicion& posSelec, Mundo* p_motorGrafico) const;
	void comprobarCasillasJaque(Mundo* motorGrafico);

	static Pieza::tipo_t seleccionarEntradaCoronar(const Movimiento& movimiento, const Tablero& tablero, const ConfiguracionDeJuego::FormasDeInteraccion& interaccion, Mundo* motorGrafico);

	DatosFinal motor(Mundo* mundoGrafico);

	void setExit(bool exit) { this->exit = exit; }
};

