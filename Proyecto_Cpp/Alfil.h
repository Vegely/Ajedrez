#ifndef _ALFIL__H_
#define	_ALFIL__H_

#include "Pieza.h"

class Alfil : public Pieza
{
	void actualizarVariables();

public:
	explicit Alfil(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_ALFIL) {}
};

#endif // !_Alfil__H_ //