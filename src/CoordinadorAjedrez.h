#pragma once
#include "MotorDeJuego.h"
#include "Mundo.h"
#include <thread>
#include "UI.h"
#include "Cliente.h"
#include "Servidor.h"
#include "Ranking.h"

#define H_MAX 25.0f
#define H_MIN -10.0f
#define W_MAX 31.5f
#define W_MIN -31.5f

enum Estado { INICIO, JUEGO, FIN, RANKING, CARGAR, MODO_LOCAL, MODO_RED, MODO, COLOR, SERVIDOR, CLIENTE, FALLO_CONEXION, PAUSA, COLOR_SERVIDOR, GUARDAR};

class CoordinadorAjedrez
{
protected:
	Estado estado;

public:
	Mundo motorGrafico;
	Ranking ranking;
	Cliente* cliente = nullptr;
	Servidor* servidor = nullptr;

	bool inicializarPartida;

	std::thread* motor = new std::thread;
	std::thread* hilo_servidor = nullptr;
	std::thread* hilo_cliente = nullptr;

	DatosFinal datosFinal;

	CoordinadorAjedrez();
	void onTimer();
	void dibuja();
	void tecla(unsigned char key);
	void teclaEspecial(int key);
	void click(int button, int state, int x, int y);

	friend class menuInicial;
};

void threadMotor(const ConfiguracionDeJuego* p_configuracion, Mundo* p_motorGrafico, DatosFinal* p_datosFinal);
void hiloServidor(CoordinadorAjedrez* ajedrez);
void hiloCliente(CoordinadorAjedrez* ajedrez);

float aCoordenadasGlutX(float p);

float aCoordenadasGlutY(float p);

void parametrosTexturasMEstados();