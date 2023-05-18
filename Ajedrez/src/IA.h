#pragma once

#include "Tablero.h"

#define PROFUNDIDAD_IA 10

class IA
{
private:
	const bool color;

	MovimientoEvaluado minimax(const Tablero& tablero, unsigned char profundidad, bool coloraMaximizar, eval_t alfa = MIN_EVAL_T, eval_t beta = MAX_EVAL_T);

public:
	IA(bool color) : color(color) {}

	Movimiento movimiento(const Tablero& tablero) { return minimax(tablero, PROFUNDIDAD_IA, color).movimiento; }
};

