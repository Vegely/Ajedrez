#pragma once

#include "Tablero.h"

struct ConfiguracionDeJuego
{
	enum class FormasDeInteraccion { LOCAL, REMOTO, IA };
	FormasDeInteraccion config[2];

	FormasDeInteraccion operator[] (int i) const { return config[i]; }
	FormasDeInteraccion operator[] (int i) { return config[i]; }
};

enum class CodigoFinal { JAQUE_MATE, REY_AHOGADO, TABLAS_POR_MATERIAL_INSUFICIENTE, TABLAS_POR_REPETICION, TABLAS_POR_PASIVIDAD };	

struct DatosFinal
{
	bool exit = false;
	CodigoFinal codigoFinal;
	bool ganador;
};

class MotorDeJuego
{
	void pintar(Posicion piezaSelec = Posicion(-1, -1)) const;	

	Movimiento seleccionarEntrada(bool pos1Selec) const;
	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec) const;
	bool hacerJugada(Movimiento movimiento);

	Pieza::tipo_t seleccionarEntradaCoronar(Posicion posicion) const;
public:
	ConfiguracionDeJuego config;
	
	Tablero tablero;

	MotorDeJuego() {}
	MotorDeJuego(ConfiguracionDeJuego config) : config(config), tablero(Tablero(true)) { pintar(); }

	void liberar() { tablero.liberar(); }

	void setConfig( ConfiguracionDeJuego config2) { config.config[0] = config.config[0];config.config[1] = config2.config[1]; }
	void initTablero() { tablero = Tablero(true); }

	DatosFinal motor();
};
