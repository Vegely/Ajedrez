#ifndef _Rey__H_
#define	_Rey__H_

#include "Pieza.h"

class Rey : public Pieza
{
	DatosClavada actualizarVariables(bool clavada, Posicion direccionClavada, bool tableroIlegalesRey[2][8][8]) override;
public:
	explicit Rey(const Tablero& p_tablero, const bool color) : Pieza(p_tablero, color, VALOR_REY, tipo_t::REY) {};
	explicit Rey(const Rey& R) : Pieza(R) {}
};

#endif // !_Rey__H_ //