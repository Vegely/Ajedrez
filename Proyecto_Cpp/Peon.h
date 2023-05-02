#ifndef _Peon__H_
#define	_Peon__H_

#include "Pieza.h"

class Peon : public Pieza
{
	void actualizarVariables();
public:
	explicit Peon(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_PEON,"PEON") {};
	explicit Peon(const Peon& P) : Pieza(P) {}
};

#endif // !_Peon__H_ //