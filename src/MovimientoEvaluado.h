#pragma once

#include "Movimiento.h"

#include <vector>

struct MovimientoEvaluado
{
	std::vector<Movimiento> movimiento;
	eval_t eval;

	explicit MovimientoEvaluado(const eval_t& eval) : eval(eval) { movimiento.clear(); }
};