#include "IA.h"
#include "MotorDeJuego.h"

#include <algorithm>

constexpr auto COEFF_DIFERENCIA_MATERIAL = 150.0;
constexpr auto COEFF_AMENAZAS_PELIGROSAS = 40.0;
constexpr auto COEFF_AMENAZAS_POCO_PELIGROSAS = 10.0;
constexpr auto VALOR_AMENAZAS_PELIGROSAS = 30000000000;
constexpr auto VALOR_JAQUE_MATE = 100000;

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


		valorTablero += (1 - 2 * !piezaAnalizada->getColor()) * piezaAnalizada->getValor(); //Resta si es negra y suma si es blanca

		for (auto piezasAmenazasAPiezaAnalizada : piezaAnalizada->getAmenazas())
		{
			if (piezaAnalizada->getValor() - piezasAmenazasAPiezaAnalizada->getValor() > 1) //Si la amenaza es peligrosa pieza de menor valor amenaza una de mayor valor
			{
				if (amenazaPeligrosa > abs(piezaAnalizada->getValor() - piezasAmenazasAPiezaAnalizada->getValor())) //Se mete la pieza de menor valor que amenenaza a la de mayor valor
					amenazaPeligrosa = (1 - 2 * piezaAnalizada->getColor()) * abs(piezaAnalizada->getValor() - piezasAmenazasAPiezaAnalizada->getValor()); //Valor con signo para suma final
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

		amenazaPocoPeligrosaReturn += (1 - 2 * piezaAnalizada->getColor()) * piezaAnalizada->getValor() * abs(proteccion / (piezaAnalizada->EstaProtegida().size() + 1) - amenazaPocoPeligrosa / (piezaAnalizada->getAmenazas().size() + 1));
	}

	if (tablero.jaqueMate())
	{
		return (1 - 2 * tablero.colorDelTurno) * VALOR_JAQUE_MATE;
	}
	bool ra = tablero.reyAhogado();
	if (ra || tablero.tablasMaterialInsuficiente() || tablero.infoTablas.tablasPorRepeticion() || tablero.infoTablas.tablasPorPasividad())
	{
		return 0;
	}

	double respuesta = COEFF_DIFERENCIA_MATERIAL* valorTablero + COEFF_AMENAZAS_PELIGROSAS * amenazaPeligrosaReturn + COEFF_AMENAZAS_POCO_PELIGROSAS * amenazaPocoPeligrosaReturn;

	if (respuesta == 1.79769e+308)
		std::cout << "CUIDADO UWU";

	return respuesta;
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

				///
				//Insertar lineas vacias para limpiar consola
				for (int i = 0; i < 8; i++) {
					std::cout << std::endl;
				}
				std::cout << (int)profundidad << std::endl;
				// Pintar el tablero
				int i = 0, j = 1;
				for (int x = 0; x < ANCHO_TABLERO * ANCHO_TABLERO; x++)
				{
					if (i % 8 == 0) std::cout << "  " << j++ << "\t"; // Pintar los numeros

					if (aux.tablero[x] == nullptr) std::cout << "---\t"; // Pintar vacio
					else std::cout << aux.tablero[x]->getNombre() << " " << aux.tablero[x]->getColor() << "\t"; // Pintar pieza


					if (i++ % 8 == 7) std::cout << "\n\n\n"; // L�neas de division de fila
				}

				std::cout << "\t";
				for (char i = 'A'; i <= 'H'; i++) std::cout << " " << i << " \t"; // Pintar las letras
				std::cout << std::endl;

				if (aux.reyAhogado() == 1)
					std::cout << "CUIDADO UWU_2";
				///

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, false, alfa, beta);
				aux.liberar();

				if (eval.eval >= maxEval.eval) // Guarda los movimientos de maximo valor en la ultima vuelta antes de salir
				{
					if (eval.eval > maxEval.eval)
						maxEval = MovimientoEvaluado(eval.eval);
					if (profundidad == PROFUNDIDAD_IA) 
						maxEval.movimiento.push_back(Movimiento(p_pieza->getPosicion(), posicion));
				}

				///
				if (profundidad == PROFUNDIDAD_IA) std::cout << eval.eval << ": " << (char)(p_pieza->getPosicion().x + 65) << ", " << p_pieza->getPosicion().y + 1 << "; " << (char)(posicion.x + 65) << ", " << posicion.y + 1 << std::endl;
				///

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

				///
				//Insertar lineas vacias para limpiar consola
				for (int i = 0; i < 8; i++) {
					std::cout << std::endl;
				}
				std::cout << (int)profundidad << std::endl;
				// Pintar el tablero
				int i = 0, j = 1;
				for (int x = 0; x < ANCHO_TABLERO * ANCHO_TABLERO; x++)
				{
					if (i % 8 == 0) std::cout << "  " << j++ << "\t"; // Pintar los numeros

					if (aux.tablero[x] == nullptr) std::cout << "---\t"; // Pintar vacio
					else std::cout << aux.tablero[x]->getNombre() << " " << aux.tablero[x]->getColor() << "\t"; // Pintar pieza


					if (i++ % 8 == 7) std::cout << "\n\n\n"; // L�neas de division de fila
				}

				std::cout << "\t";
				for (char i = 'A'; i <= 'H'; i++) std::cout << " " << i << " \t"; // Pintar las letras
				std::cout << std::endl;

				if (aux.reyAhogado() == 1)
					std::cout << "CUIDADO UWU_2";
				///

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, false, alfa, beta);
				aux.liberar();

				if (eval.eval >= maxEval.eval) // Guarda los movimientos de maximo valor en la ultima vuelta antes de salir
				{
					if (eval.eval > maxEval.eval) maxEval = MovimientoEvaluado(eval.eval);
					if (profundidad == PROFUNDIDAD_IA) maxEval.movimiento.push_back(Movimiento(p_pieza->getPosicion(), p_piezaComida->getPosicion()));
				}

				///
				if (profundidad == PROFUNDIDAD_IA) std::cout << eval.eval << ": " << (char)(p_pieza->getPosicion().x + 65) << ", " << p_pieza->getPosicion().y + 1 << "; " << (char)(p_piezaComida->getPosicion().x + 65) << ", " << p_piezaComida->getPosicion().y + 1 << std::endl;
				///

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

				///
				//Insertar lineas vacias para limpiar consola
				for (int i = 0; i < 8; i++) {
					std::cout << std::endl;
				}
				std::cout << (int)profundidad << std::endl;
				// Pintar el tablero
				int i = 0, j = 1;
				for (int x = 0; x < ANCHO_TABLERO * ANCHO_TABLERO; x++)
				{
					if (i % 8 == 0) std::cout << "  " << j++ << "\t"; // Pintar los numeros

					if (aux.tablero[x] == nullptr) std::cout << "---\t"; // Pintar vacio
					else std::cout << aux.tablero[x]->getNombre() << " " << aux.tablero[x]->getColor() << "\t"; // Pintar pieza


					if (i++ % 8 == 7) std::cout << "\n\n\n"; // L�neas de division de fila
				}

				std::cout << "\t";
				for (char i = 'A'; i <= 'H'; i++) std::cout << " " << i << " \t"; // Pintar las letras
				std::cout << std::endl;

				if (aux.reyAhogado() == 1)
					std::cout << "CUIDADO UWU_2";
				///

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, true, alfa, beta);
				aux.liberar();

				if (eval.eval <= minEval.eval) // Guarda los movimientos de maximo valor en la ultima vuelta antes de salir
				{
					if (eval.eval < minEval.eval) minEval = MovimientoEvaluado(eval.eval);
					if (profundidad == PROFUNDIDAD_IA) minEval.movimiento.push_back(Movimiento(p_pieza->getPosicion(), posicion));
				}

				///
				if (profundidad == PROFUNDIDAD_IA) std::cout << eval.eval << ": " << (char)(p_pieza->getPosicion().x + 65) << ", " << p_pieza->getPosicion().y + 1 << "; " << (char)(posicion.x + 65) << ", " << posicion.y + 1 << std::endl;
				///

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

				///
				//Insertar lineas vacias para limpiar consola
				for (int i = 0; i < 8; i++) {
					std::cout << std::endl;
				}
				std::cout << (int)profundidad << std::endl;
				// Pintar el tablero
				int i = 0, j = 1;
				for (int x = 0; x < ANCHO_TABLERO * ANCHO_TABLERO; x++)
				{
					if (i % 8 == 0) std::cout << "  " << j++ << "\t"; // Pintar los numeros

					if (aux.tablero[x] == nullptr) std::cout << "---\t"; // Pintar vacio
					else std::cout << aux.tablero[x]->getNombre() << " " << aux.tablero[x]->getColor() << "\t"; // Pintar pieza


					if (i++ % 8 == 7) std::cout << "\n\n\n"; // L�neas de division de fila
				}

				std::cout << "\t";
				for (char i = 'A'; i <= 'H'; i++) std::cout << " " << i << " \t"; // Pintar las letras
				std::cout << std::endl;

				if (aux.reyAhogado() == 1)
					std::cout << "CUIDADO UWU_2";
				///

				MovimientoEvaluado eval = minimax(aux, profundidad - 1, true, alfa, beta);
				aux.liberar();

				if (eval.eval <= minEval.eval) // Guarda los movimientos de maximo valor en la ultima vuelta antes de salir
				{
					if (eval.eval < minEval.eval) minEval = MovimientoEvaluado(eval.eval);
					if (profundidad == PROFUNDIDAD_IA) minEval.movimiento.push_back(Movimiento(p_pieza->getPosicion(), p_piezaComida->getPosicion()));
				}
				///
				if (profundidad == PROFUNDIDAD_IA) std::cout << eval.eval << ": " << (char)(p_pieza->getPosicion().x + 65) << ", " << p_pieza->getPosicion().y + 1 << "; " << (char)(p_piezaComida->getPosicion().x + 65) << ", " << p_piezaComida->getPosicion().y + 1 << std::endl;
				///
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

	///
	Movimiento movimiento = movimientoEvaluado.movimiento.at(rand() % movimientoEvaluado.movimiento.size());
	std::cout << "Movimiento: " << (char)(movimiento.inicio.x + 65) << ", " << movimiento.inicio.y + 1 << "; " << (char)(movimiento.fin.x + 65) << ", " << movimiento.fin.y + 1 << std::endl;
	std::cout << "Evaluacion del tablero: " << movimientoEvaluado.eval << std::endl;
	///

	return movimiento;
}

Pieza::tipo_t IA::coronar(const Tablero& tablero, Posicion posicion)
{
	std::vector<Pieza::tipo_t> tiposBuenos;
	eval_t eval((1 - 2 * tablero.colorDelTurno) * MAX_EVAL_T);

	Pieza::tipo_t tipos[] = { Pieza::tipo_t::DAMA, Pieza::tipo_t::ALFIL, Pieza::tipo_t::TORRE, Pieza::tipo_t::CABALLO };
	for (Pieza::tipo_t tipo : tipos)
	{
		Tablero aux = Tablero::copiar(tablero);

		Pieza* p_pieza = aux.leer(posicion);
		aux.coronar(posicion, tipo);
		aux.mover(Movimiento(posicion, posicion + (1 - 2 * !tablero.leer(posicion)->getColor()) * Posicion(0, 1)));
		delete p_pieza;

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
