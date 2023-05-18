#ifndef _TORRE__H_
#define	_TORRE__H_

#include "Pieza.h"

class Torre : public Pieza
{
	void actualizarVariables();
	bool puedeEnrocar = true; //Si se mueve pierde la posibilidad de enrocar
public:
	explicit Torre(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_TORRE, tipo_t::TORRE) {}
	explicit Torre(const Torre& T) : Pieza(T) {}

	std::string getNombre() const override { return "T"; }
};

#endif // !_Torre__H_ //