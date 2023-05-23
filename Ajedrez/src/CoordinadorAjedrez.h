#pragma once
#include "Mundo.h"


enum Estado { INICIO, JUEGO, PAUSA, FIN };

class CoordinadorAjedrez
{
protected:
	Estado estado;
public:
	Mundo mundo;
	CoordinadorAjedrez();
	void inicializa();
	void dibuja();
	void tecla(unsigned char key);
	void click(int button, int state, int x, int y);

	friend class menuInicial;
};

