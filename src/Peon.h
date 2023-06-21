#ifndef _Peon__H_
#define	_Peon__H_

#include "Pieza.h"

class Peon : public Pieza
{
	DatosClavada actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) override;
public:
	explicit Peon(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_PEON, tipo_t::PEON) {};
	explicit Peon(const Peon& P) : Pieza(P) {}
};

#endif // !_Peon__H_ //