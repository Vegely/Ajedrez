#pragma once

#include "Posicion.h"

typedef int eval_t;
#define MIN_EVAL_T INT_MIN
#define MAX_EVAL_T INT_MAX

struct Movimiento
{
	Posicion inicio, fin;

	Movimiento() {}
	Movimiento(Posicion inicio, Posicion fin) : inicio(inicio), fin(fin) {}
};

struct MovimientoEvaluado
{
	Movimiento movimiento;
	eval_t eval;

	MovimientoEvaluado() {}
	MovimientoEvaluado(Movimiento movimiento, eval_t eval) : movimiento(movimiento), eval(eval) {}
};