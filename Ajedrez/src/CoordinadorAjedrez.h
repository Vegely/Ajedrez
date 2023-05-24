#pragma once
#include "Mundo.h"


enum Estado { INICIO, JUEGO, PAUSA, FIN, CARGAR, NUEVA, MODO, JUGADOR1, JUGADOR2, RANKING, EXISTE, NO_EXISTE, SALAS, CREAR_SALA, UNIRSE_SALA, ERROR_SALA};

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

