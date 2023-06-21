#ifndef _CONFIGURACIONDEJUEGO__H_
#define _CONFIGURACIONDEJUEGO__H_

#include "ElementoRed.h"

struct ConfiguracionDeJuego
{
	enum class FormasDeInteraccion { LOCAL, IA, EMISOR, RECEPTOR };
	FormasDeInteraccion config[2];

	/*ElementoRed* elementoRed = nullptr;*/

	FormasDeInteraccion  operator[] (int i) const { return config[i]; }
	FormasDeInteraccion& operator[] (int i) { return config[i]; }
};

#endif // !_CONFIGURACIONDEJUEGO__H_