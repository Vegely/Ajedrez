#ifndef _Caballo__H_
#define	_Caballo__H_

#include "Pieza.h"

class Caballo : public Pieza
{
	void actualizarVariables();
public:
	explicit Caballo(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_CABALLO,"CABALLO") {}
	explicit Caballo(const Caballo& C) : Pieza(C) {}
};

#endif // !_Caballo__H_ //
