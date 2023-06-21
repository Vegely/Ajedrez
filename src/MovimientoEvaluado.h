#ifndef _MOVIMIENTOEVALUADO__H_
#define _MOVIMIENTOEVALUADO__H_

#include "Movimiento.h"

#include <vector>

struct MovimientoEvaluado
{
	std::vector<Movimiento> movimiento;
	eval_t eval;

	explicit MovimientoEvaluado(const eval_t& eval) : eval(eval) { movimiento.clear(); }
};

#endif // !_MOVIMIENTOEVALUADO__H_