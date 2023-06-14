#pragma once

#include "Tablero.h"

#define PROFUNDIDAD_IA 3

class IA
{
	static MovimientoEvaluado minimax(const Tablero& tablero, unsigned char profundidad, bool coloraMaximizar, eval_t alfa = MIN_EVAL_T, eval_t beta = MAX_EVAL_T);

public:
	static Movimiento mover(const Tablero& tablero);
	static double evaluacion(const Tablero& tablero);
	static Pieza::tipo_t coronar(const Tablero& tablero, Posicion posicion);
};

