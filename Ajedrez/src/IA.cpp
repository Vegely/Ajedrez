#include "IA.h"
#include "MotorDeJuego.h"

#include <algorithm>

constexpr auto COEFF_DIFERENCIA_MATERIAL = 50.0;
constexpr auto COEFF_AMENAZAS_PELIGROSAS = 40.0;
constexpr auto COEFF_AMENAZAS_POCO_PELIGROSAS = 10.0;
constexpr auto VALOR_AMENAZAS_PELIGROSAS = 1.79769e+308;

double IA::evaluacion(const Tablero& tablero)  //Valor negativo ventaja negras valor positivo ventaja blancas
{
	double amenazaPeligrosa = VALOR_AMENAZAS_PELIGROSAS; //Valor para luego comparar si hay amenazas de piezas de menor a piezas de mayor valor (se pone a un valor de error)
	double amenazaPocoPeligrosa = 0;		//Valor para registrar valor de amenazas de mayor valor a una pieza de menor valor
	double proteccion = 0;					//Valor de piezas que defienden de una amenaza poco peligrosa
	double valorTablero = 0;

	//Para llevar la cuenta
	double amenazaPeligrosaReturn = 0;
	double amenazaPocoPeligrosaReturn = 0;

	for (auto piezaAnalizada : tablero.tablero) if(piezaAnalizada != nullptr)
	{

		//Se reinicializan los valores en cada ciclo
		amenazaPeligrosa = VALOR_AMENAZAS_PELIGROSAS;
		amenazaPocoPeligrosa = 0;
		proteccion = 0;


		valorTablero += pow(-1, 1 + piezaAnalizada->getColor()) * piezaAnalizada->getValor(); //Resta si es negra y suma si es blanca

		for (auto piezasAmenazasAPiezaAnalizada : piezaAnalizada->getAmenazas())
		{
			if (piezaAnalizada->getValor() - piezasAmenazasAPiezaAnalizada->getValor() > 1) //Si la amenaza es peligrosa pieza de menor valor amenaza una de mayor valor
			{
				if (amenazaPeligrosa > abs(piezaAnalizada->getValor() - piezasAmenazasAPiezaAnalizada->getValor())) //Se mete la pieza de menor valor que amenenaza a la de mayor valor
					amenazaPeligrosa = pow(-1, piezaAnalizada->getColor()) * abs(piezaAnalizada->getValor() - piezasAmenazasAPiezaAnalizada->getValor()); //Valor con signo para suma final
			}
			else
			{
				amenazaPocoPeligrosa += piezasAmenazasAPiezaAnalizada->getValor(); //Valor sin signo temporal
			}
		}
		for (auto piezasDefiendenAPiezaAnalizada : piezaAnalizada->EstaProtegida())
		{
			proteccion += piezasDefiendenAPiezaAnalizada->getValor(); //Valor sin signo temporal
		}

		if (amenazaPeligrosa != VALOR_AMENAZAS_PELIGROSAS)
		{
			amenazaPeligrosaReturn += amenazaPeligrosa;
		}

		amenazaPocoPeligrosaReturn += pow(-1, piezaAnalizada->getColor()) * piezaAnalizada->getValor() * abs(proteccion / piezaAnalizada->EstaProtegida().size() - amenazaPocoPeligrosa / piezaAnalizada->getAmenazas().size());
	}

	return COEFF_DIFERENCIA_MATERIAL * valorTablero + COEFF_AMENAZAS_PELIGROSAS * amenazaPeligrosaReturn + COEFF_AMENAZAS_POCO_PELIGROSAS * amenazaPeligrosaReturn;
}

MovimientoEvaluado IA::minimax(const Tablero& tablero, unsigned char profundidad, bool coloraMaximizar, eval_t alfa, eval_t beta)
{
	if (profundidad == 0 || tablero.jaqueMate()) { return MovimientoEvaluado(evaluacion(tablero)); }

	if (coloraMaximizar)
	{
		MovimientoEvaluado maxEval(MIN_EVAL_T);

		bool exit = false;
		for (Pieza* p_pieza : tablero.tablero) if (p_pieza != nullptr && p_pieza->getColor() == coloraMaximizar)
		{
			for (Posicion posicion : p_pieza->getPuedeMover())
			{
				Tablero aux = Tablero::copiar(tablero);
				aux.mover(Movimiento(p_pieza->getPosicion(), posicion));

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, false, alfa, beta);
				aux.liberar();

				if (eval.eval >= maxEval.eval) // Guarda los movimientos de maximo valor en la ultima vuelta antes de salir
				{
					if (eval.eval > maxEval.eval)
						maxEval = MovimientoEvaluado(eval.eval);
					if (profundidad == PROFUNDIDAD_IA) 
						maxEval.movimiento.push_back(Movimiento(p_pieza->getPosicion(), posicion));
				}

				alfa = std::max(alfa, eval.eval);

				if (beta <= alfa)
				{
					exit = true;
					break;
				}
			}

			if (!exit) for (Pieza* p_piezaComida : p_pieza->getPuedeComer())
			{
				Tablero aux = Tablero::copiar(tablero);
				aux.mover(Movimiento(p_pieza->getPosicion(), p_piezaComida->getPosicion()));

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, false, alfa, beta);
				aux.liberar();

				if (eval.eval >= maxEval.eval) // Guarda los movimientos de maximo valor en la ultima vuelta antes de salir
				{
					if (eval.eval > maxEval.eval) maxEval = MovimientoEvaluado(eval.eval);
					if (profundidad == PROFUNDIDAD_IA) maxEval.movimiento.push_back(Movimiento(p_pieza->getPosicion(), p_piezaComida->getPosicion()));
				}

				alfa = std::max(alfa, eval.eval);

				if (beta <= alfa)
				{
					exit = true;
					break;
				}
			}
			if (exit) break;
		}
		return maxEval;
	}

	else
	{
		MovimientoEvaluado minEval(MAX_EVAL_T);

		bool exit = false;
		for (Pieza* p_pieza : tablero.tablero) if (p_pieza != nullptr && p_pieza->getColor() == coloraMaximizar)
		{
			for (Posicion posicion : p_pieza->getPuedeMover())
			{
				Tablero aux = Tablero::copiar(tablero);
				aux.mover(Movimiento(p_pieza->getPosicion(), posicion));

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, true, alfa, beta);
				aux.liberar();

				if (eval.eval <= minEval.eval) // Guarda los movimientos de maximo valor en la ultima vuelta antes de salir
				{
					if (eval.eval < minEval.eval) minEval = MovimientoEvaluado(eval.eval);
					if (profundidad == PROFUNDIDAD_IA) minEval.movimiento.push_back(Movimiento(p_pieza->getPosicion(), posicion));
				}

				beta = std::min(beta, eval.eval);

				if (beta <= alfa)
				{
					exit = true;
					break;
				}
			}

			if (!exit) for (Pieza* p_piezaComida : p_pieza->getPuedeComer())
			{
				Tablero aux = Tablero::copiar(tablero);
				aux.mover(Movimiento(p_pieza->getPosicion(), p_piezaComida->getPosicion()));

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, true, alfa, beta);
				aux.liberar();

				if (eval.eval <= minEval.eval) // Guarda los movimientos de maximo valor en la ultima vuelta antes de salir
				{
					if (eval.eval < minEval.eval) minEval = MovimientoEvaluado(eval.eval);
					if (profundidad == PROFUNDIDAD_IA) minEval.movimiento.push_back(Movimiento(p_pieza->getPosicion(), p_piezaComida->getPosicion()));
				}

				beta = std::min(beta, eval.eval);

				if (beta <= alfa)
				{
					exit = true;
					break;
				}
			}
			if (exit) break;
		}
		return minEval;
	}
}

Movimiento IA::mover(const Tablero& tablero)
{
	MovimientoEvaluado movimientoEvaluado = minimax(tablero, PROFUNDIDAD_IA, tablero.colorDelTurno);

	return movimientoEvaluado.movimiento.at(rand() % movimientoEvaluado.movimiento.size());
}

Pieza::tipo_t IA::coronar(const Tablero& tablero, Posicion posicion)
{
	std::vector<Pieza::tipo_t> tiposBuenos;
	eval_t eval(-1 * tablero.colorDelTurno * MAX_EVAL_T);

	Pieza::tipo_t tipos[] = { Pieza::tipo_t::DAMA, Pieza::tipo_t::ALFIL, Pieza::tipo_t::TORRE, Pieza::tipo_t::CABALLO };
	for (Pieza::tipo_t tipo : tipos)
	{
		Tablero aux = Tablero::copiar(tablero);

		delete aux.tablero[posicion.indice()];
		aux.coronar(posicion - 1 * tablero.colorDelTurno * Posicion(0, 1), tipo);

		MovimientoEvaluado movimientoEvaluado = minimax(tablero, PROFUNDIDAD_IA, tablero.colorDelTurno);

		if ((tablero.colorDelTurno && movimientoEvaluado.eval > eval) || (!tablero.colorDelTurno && movimientoEvaluado.eval < eval))
		{
			eval = movimientoEvaluado.eval;
			tiposBuenos.push_back(tipo);
		}

		aux.liberar();
	}
	
	return tiposBuenos.at(rand() % tiposBuenos.size());
}
