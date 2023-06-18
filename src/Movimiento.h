#pragma once

#include <string>
#include <limits>

#include "Posicion.h"

typedef double eval_t;
#define MIN_EVAL_T -DBL_MAX
#define MAX_EVAL_T DBL_MAX

struct Movimiento
{
	Posicion inicio, fin;

	Movimiento() {}
	Movimiento(Posicion inicio, Posicion fin) : inicio(inicio), fin(fin) {}
	Movimiento(std::string str) { if (str.size() == 7 && str[1] == ' ' && str[3] == ' ' && str[5] == ' ') *this = Movimiento(Posicion(str[0] - '0', str[2] - '0'), Posicion(str[4] - '0', str[6] - '0')); }

	std::string toString() const { return std::to_string(inicio.x) + " " + std::to_string(inicio.y) + " " + std::to_string(fin.x) + " " + std::to_string(fin.y); }

	Movimiento operator- () { return Movimiento(this->fin, this->inicio); }

	bool operator== (const Movimiento& rhs) const { return (this->inicio == rhs.inicio && this->fin == rhs.fin); }
	bool operator!= (const Movimiento& rhs) const { return !(*this == rhs); }
};

struct MovimientoEvaluado
{
	std::vector<Movimiento> movimiento;
	eval_t eval;
	
	explicit MovimientoEvaluado(const eval_t& eval) : eval(eval) { movimiento.clear(); }
};