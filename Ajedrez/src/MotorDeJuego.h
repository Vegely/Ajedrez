#pragma once

#include "Tablero.h"
#include "CoordinadorAjedrez.h"

struct ConfiguracionDeJuego
{
	enum class FormasDeInteraccion { LOCAL, IA };
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
	Mundo* p_motorGrafico = nullptr;

	void pintar(Posicion piezaSelec = Posicion(-1, -1)) const;	

	Movimiento seleccionarEntrada(bool pos1Selec) const;
	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec) const;
	bool hacerJugada(Movimiento movimiento);

	Pieza::tipo_t seleccionarEntradaCoronar(Posicion posicion) const;
public:
	ConfiguracionDeJuego config;
	
	Tablero tablero;

	MotorDeJuego() {}
	MotorDeJuego(ConfiguracionDeJuego config, Mundo* p_motorGrafico) : config(config), p_motorGrafico(p_motorGrafico), tablero(Tablero(true)) { pintar(); }

	void liberar() { tablero.liberar(); }

	DatosFinal motor();
};

