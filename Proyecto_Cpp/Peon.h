#ifndef _Peon__H_
#define	_Peon__H_

#include "Pieza.h"

class Peon : public Pieza
{
	void actualizarVariables();
public:
	Peon(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_PEON,"PEON") {};
	
};

#endif // !_Peon__H_ //