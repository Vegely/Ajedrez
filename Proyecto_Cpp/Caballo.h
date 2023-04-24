#ifndef _Caballo__H_
#define	_Caballo__H_

#include "Pieza.h"

class Caballo : public Pieza
{
public:
	Caballo(int val) :valor(val) {}
	void mover();
};

#endif // !_Caballo__H_ //
