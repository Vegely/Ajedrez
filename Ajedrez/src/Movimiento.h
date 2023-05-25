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

	Movimiento operator- () { return Movimiento(this->fin, this->inicio); }

	bool operator== (const Movimiento& rhs) const { return (this->inicio == rhs.inicio && this->fin == rhs.fin); }
	bool operator!= (const Movimiento& rhs) const { return !(*this == rhs); }
};

struct MovimientoEvaluado
{
	std::vector<Movimiento> movimiento;
	eval_t eval;
	
	explicit MovimientoEvaluado(eval_t eval) : eval(eval) { movimiento.clear(); }
};