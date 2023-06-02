#ifndef _DAMA__H_
#define	_DAMA__H_

#include "Pieza.h"

class Dama : public Pieza
{
	DatosClavada actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) override;

public:
	explicit Dama(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_DAMA, tipo_t::DAMA) {}
	explicit Dama(const Dama& R) : Pieza(R) {}

	std::string getNombre() const override { return "D"; }
};

#endif // !_DAMA__H_ //