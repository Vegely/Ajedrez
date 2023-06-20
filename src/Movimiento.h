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
	
	Movimiento(Posicion inicio = Posicion(), Posicion fin = Posicion()) : inicio(inicio), fin(fin) {}
	Movimiento(const std::string& str);

	std::string toString() const { return std::to_string(inicio.x) + " " + std::to_string(inicio.y) + " " + std::to_string(fin.x) + " " + std::to_string(fin.y); }

	Movimiento operator- () { return Movimiento(this->fin, this->inicio); }

	bool operator== (const Movimiento& rhs) const { return (this->inicio == rhs.inicio && this->fin == rhs.fin); }
	bool operator!= (const Movimiento& rhs) const { return !(*this == rhs); }
};