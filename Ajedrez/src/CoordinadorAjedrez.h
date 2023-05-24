#pragma once
#include "Mundo.h"
#include "Ranking.h"
#include "Servidor.h"
#include "Cliente.h"
#include <thread>


enum Estado { INICIO, NUEVA_PARTIDA, MODO, J1,J2, JUEGO, PAUSA, CARGAR_PARTIDA,RANKING,PARTIDA_EXISTE, PARTIDA_NO_EXISTE, CREAR_SALA, UNIRSE_SALA };

class CoordinadorAjedrez
{
protected:
	Estado estado;

	std::string mov_cliente = "hola";
	std::string mov_servidor = "";
public:
	Mundo mundo;
	Partida datosPartida;
	Ranking ranking;
	Cliente cliente;
	Servidor* servidor = new Servidor;
	std::thread* hilo_servidor = nullptr;

	CoordinadorAjedrez();
	void inicializa();
	void dibuja();
	void tecla(unsigned char key);
	void teclaEspecial(int key);
	void click(int button, int state, int x, int y);

	friend class menuInicial;
};




