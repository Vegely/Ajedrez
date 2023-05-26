#pragma once
#include "Mundo.h"
#include "Ranking.h"
#include "Servidor.h"
#include "Cliente.h"
#include "MotorDeJuego.h"
#include <thread>


enum Estado { INICIO, NUEVA_PARTIDA, MODO, J1,J2, JUEGO, PAUSA, CARGAR_PARTIDA,RANKING,PARTIDA_EXISTE, PARTIDA_NO_EXISTE, CREAR_SALA, UNIRSE_SALA,
				INIT, COLORJ1, NO_CONECTADO};

class CoordinadorAjedrez
{
protected:
	Estado estado;

	std::string mov_cliente = "1";
	std::string mov_servidor = "";

	bool turno = 0; //0 -> cliente, 1 -> servidor
	bool salir = 0;
	bool reset = 0;
public:
	bool inicializarPartida;

	Mundo mundo;
	Partida datosPartida;
	Ranking ranking;
	Cliente* cliente = new Cliente;
	Servidor* servidor = new Servidor;
	std::thread* hilo_servidor = nullptr;
	std::thread* hilo_cliente = nullptr;

	CoordinadorAjedrez();
	void dibuja();
	void tecla(unsigned char key);
	void teclaEspecial(int key);
	void click(int button, int state, int x, int y);

	friend class menuInicial;
};

void hiloServidor(Servidor* servidor, std::string* mov_cliente, Estado* estado, bool* salir, std::string* m_cliente, bool* reset);
void hiloCliente(Cliente* cliente, Estado* estado, bool* salir, std::string* m_servidor, bool* reset);




