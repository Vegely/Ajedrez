#pragma once

#include "Tablero.h"
#include "Mundo.h"

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
	const ConfiguracionDeJuego config;
	Tablero tablero;

	//void pintar(Posicion piezaSelec = Posicion(-1, -1)) const;
	Movimiento seleccionarEntrada(Mundo* p_motorGrafico, bool pos1Selec);
	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec) const;
	bool hacerJugada(Movimiento movimiento, Mundo* motorGrafico);

	Pieza::tipo_t seleccionarEntradaCoronar(Posicion posicion, Mundo* motorGrafico) const;

public:
	MotorDeJuego(const ConfiguracionDeJuego& config) : config(config), tablero(Tablero(true)) { /*pintar()*/; }
	Tablero* getTablero(void) { return &this->tablero; }
	void liberar() { tablero.liberar(); }

	DatosFinal motor(Mundo* mundoGrafico);
};

