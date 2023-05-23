#pragma once
#include "Mundo.h"
#include "Ranking.h"


enum Estado { INICIO, NUEVA_PARTIDA, MODO, J1,J2, JUEGO, PAUSA, CARGAR_PARTIDA,RANKING,PARTIDA_EXISTE, PARTIDA_NO_EXISTE };

class CoordinadorAjedrez
{
protected:
	Estado estado;
public:
	Mundo mundo;
	Partida datosPartida;
	Ranking ranking;

	CoordinadorAjedrez();
	void inicializa();
	void dibuja();
	void tecla(unsigned char key);
	void teclaEspecial(int key);
	void click(int button, int state, int x, int y);

	friend class menuInicial;
};




