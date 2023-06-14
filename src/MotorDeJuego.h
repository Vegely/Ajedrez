#pragma once

#include "Tablero.h"
#include "Mundo.h"
#include "IA.h";

struct ConfiguracionDeJuego
{
	enum class FormasDeInteraccion { LOCAL, IA };
	FormasDeInteraccion config[2];

	FormasDeInteraccion operator[] (int i) const { return config[i]; }
	FormasDeInteraccion& operator[] (int i) { return config[i]; }
};

enum class CodigoFinal { JAQUE_MATE, REY_AHOGADO, TABLAS_POR_MATERIAL_INSUFICIENTE, TABLAS_POR_REPETICION, TABLAS_POR_PASIVIDAD };	

struct DatosFinal
{
	CodigoFinal codigoFinal;
	bool ganaBlanco;
};

class MotorDeJuego
{
	static ConfiguracionDeJuego config;
	
	Tablero tablero;

	void pintar(Posicion piezaSelec = Posicion(-1, -1)) const;

	Movimiento seleccionarEntrada(bool pos1Selec) const;
	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec) const;
	
public:
	MotorDeJuego(const ConfiguracionDeJuego& config) : tablero(Tablero(true)) { pintar(); this->config = config; }

	static Pieza::tipo_t seleccionarEntradaCoronar(const Posicion& posicion, const Tablero& tablero);
	//static bool hacerJugada(Movimiento movimiento, Tablero& tablero, const ConfiguracionDeJuego& config);

	void liberar() { tablero.liberar(); }

	DatosFinal motor();
};

