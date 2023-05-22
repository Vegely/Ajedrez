#pragma once

#include "Tablero.h"

class MotorDeJuego
{
	Tablero tablero;

	void pintar(Posicion piezaSelec = Posicion(-1, -1));

public:
	MotorDeJuego() { pintar(); }

	//void inicializar();
	bool hacerJugada(Movimiento movimiento);

	Movimiento ensamblarMovimiento(Posicion posicion, bool pos1Selec);
};

