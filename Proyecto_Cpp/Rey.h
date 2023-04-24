#ifndef _Rey__H_
#define	_Rey__H_

#include "Pieza.h"

class Rey : public Pieza
{
	void actualizarVariables();
public:
	Rey(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_TORRE) {};
};

#endif // !_Rey__H_ //