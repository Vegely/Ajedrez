#ifndef _DAMA__H_
#define	_DAMA__H_

#include "Pieza.h"

class Dama : public Pieza
{
	void actualizarVariables();

public:
	explicit Dama(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_DAMA, "DAMA") {}
	explicit Dama(const Dama& R) : Pieza(R) {}
};

#endif // !_DAMA__H_ //