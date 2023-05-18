#ifndef _Peon__H_
#define	_Peon__H_

#include "Pieza.h"

class Peon : public Pieza
{
	void actualizarVariables();
public:
	explicit Peon(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_PEON, tipo_t::PEON) {};
	explicit Peon(const Peon& P) : Pieza(P) {}

	std::string getNombre() const override { return "P"; }
};

#endif // !_Peon__H_ //