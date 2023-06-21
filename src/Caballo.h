#ifndef _Caballo__H_
#define	_Caballo__H_

#include "Pieza.h"

class Caballo : public Pieza
{
	DatosClavada actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) override;
public:
	explicit Caballo(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_CABALLO, tipo_t::CABALLO) {}
	explicit Caballo(const Caballo& C) : Pieza(C) {}
};

#endif // !_Caballo__H_ //
