#ifndef _TORRE__H_
#define	_TORRE__H_

#include "Pieza.h"

class Torre : public Pieza
{
	void actualizarVariables();

public:
	explicit Torre(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_TORRE,"TORRE") {}
	explicit Torre(const Torre& T) : Pieza(T) {}
};

#endif // !_Torre__H_ //