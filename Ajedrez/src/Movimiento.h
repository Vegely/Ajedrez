#pragma once

#include "Posicion.h"

#include <limits>

typedef double eval_t;
#define MIN_EVAL_T -DBL_MAX
#define MAX_EVAL_T DBL_MAX

struct Movimiento
{
	Posicion inicio, fin;

	Movimiento() {}
	Movimiento(Posicion inicio, Posicion fin) : inicio(inicio), fin(fin) {}
	Movimiento(const std::string& str) { std::stringstream ss; ss << str; ss >> inicio.x >> inicio.y >> fin.x >> fin.y; }

	inline std::string toString() { std::string str; str += inicio.x + ' ' + inicio.y + ' ' + fin.x + ' ' + fin.y; return str; }

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