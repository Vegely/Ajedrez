#ifndef _REINA__H_
#define	_REINA__H_

#include "Pieza.h"

#define VALOR_REINA 9

class Reina : public Pieza
{
	void actualizarVariables();

public:
	explicit Reina(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_REINA) {}
};

#endif // !_Dama__H_ //