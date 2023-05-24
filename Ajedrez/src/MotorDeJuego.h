#pragma once

#include "Tablero.h"

enum class CodigoFinal { JAQUE_MATE, REY_AHOGADO, TABLAS_POR_MATERIAL_INSUFICIENTE, TABLAS_POR_REPETICION, TABLAS_POR_PASIVIDAD };	

struct DatosFinal
{
	bool ganador;
	CodigoFinal codigoFinal;
};

class MotorDeJuego
{
	Tablero tablero;

	void pintar(Posicion piezaSelec = Posicion(-1, -1)) const;
	void coronar(Posicion posicion);

public:
	MotorDeJuego() { pintar(); }

	DatosFinal motor();

	bool hacerJugada(Movimiento movimiento);

	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec) const;
};

