#ifndef _TORRE__H_
#define	_TORRE__H_

#include "Pieza.h"

#define VALOR_TORRE 5

class Torre : public Pieza
{
	void actualizarVariables();

public:
	explicit Torre(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_TORRE) {}
};

#endif // !_Torre__H_ //