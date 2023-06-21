#ifndef _ALFIL__H_
#define	_ALFIL__H_

#include "Pieza.h"

class Alfil : public Pieza
{
	DatosClavada actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) override;

public:
	explicit Alfil(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_ALFIL, tipo_t::ALFIL) {}
	explicit Alfil(const Alfil& A) : Pieza(A) {}
};

#endif // !_Alfil__H_ //