#ifndef _TORRE__H_
#define	_TORRE__H_

#include "Pieza.h"

class Torre : public Pieza
{
	DatosClavada actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) override;
public:
	explicit Torre(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_TORRE, tipo_t::TORRE) {}
	explicit Torre(const Torre& T) : Pieza(T) {}
};

#endif // !_Torre__H_ //