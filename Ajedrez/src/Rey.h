#ifndef _Rey__H_
#define	_Rey__H_

#include "Pieza.h"

class Rey : public Pieza
{
	void actualizarVariables();
	bool puedeEnrocar = true; //Si se mueve pierde la posibilidad de enrocar
public:
	explicit Rey(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_REY, tipo_t::REY) {};
	explicit Rey(const Rey& R) : Pieza(R) {}

	std::string getNombre() const override { return "R"; }
};

#endif // !_Rey__H_ //