#pragma once
#include "Mundo.h"


class CoordinadorAjedrez
{
protected:
	enum Estado{INICIO, JUEGO, PAUSA, FIN};
	Estado estado; 

public:
	Mundo mundo;

	CoordinadorAjedrez();
	void inicializa();
	void dibuja();
	void tecla(unsigned char key);

	friend class menuInicial;
};

