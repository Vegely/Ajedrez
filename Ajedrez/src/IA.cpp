#include "IA.h"

#include <algorithm>

#define evaluacion() 0

MovimientoEvaluado IA::minimax(const Tablero& tablero, unsigned char profundidad, bool coloraMaximizar, eval_t alfa, eval_t beta)
{
	if (profundidad == 0 || tablero.jaqueMate()) { return MovimientoEvaluado(Movimiento(), evaluacion()); }

	if (coloraMaximizar)
	{
		MovimientoEvaluado maxEval;
		maxEval.eval = MIN_EVAL_T;
		for (Pieza* p_pieza : tablero.tablero) if (p_pieza->getColor() == coloraMaximizar)
		{
			for (Posicion posicion : p_pieza->getPuedeMover())
			{
				Tablero aux(tablero);
				aux.mover(Movimiento(p_pieza->getPosicion(), posicion));

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, false, alfa, beta);

				maxEval.eval = std::max(maxEval.eval, eval.eval);
				alfa = std::max(alfa, eval.eval);

				if (beta <= alfa) break;
			}

			for (Pieza* p_piezaComida : p_pieza->getPuedeComer())
			{
				Tablero aux(tablero);
				aux.mover(Movimiento(p_pieza->getPosicion(), p_piezaComida->getPosicion()));

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, false, alfa, beta);

				maxEval.eval = std::max(maxEval.eval, eval.eval);
				alfa = std::max(alfa, eval.eval);

				if (beta <= alfa) break;
			}
		}
		return maxEval;
	}

	else
	{
		MovimientoEvaluado minEval;
		minEval.eval = MAX_EVAL_T;
		for (Pieza* p_pieza : tablero.tablero) if (p_pieza->getColor() == coloraMaximizar)
		{
			for (Posicion posicion : p_pieza->getPuedeMover())
			{
				Tablero aux(tablero);
				aux.mover(Movimiento(p_pieza->getPosicion(), posicion));

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, true, alfa, beta);

				minEval.eval = std::min(minEval.eval, eval.eval);
				beta = std::min(beta, eval.eval);

				if (beta <= alfa) break;
			}

			for (Pieza* p_piezaComida : p_pieza->getPuedeComer())
			{
				Tablero aux(tablero);
				aux.mover(Movimiento(p_pieza->getPosicion(), p_piezaComida->getPosicion()));

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, true, alfa, beta);

				minEval.eval = std::min(minEval.eval, eval.eval);
				beta = std::min(beta, eval.eval);

				if (beta <= alfa) break;
			}
		}
		return minEval;
	}
}