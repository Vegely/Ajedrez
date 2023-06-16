#pragma once
#include "MotorDeJuego.h"
#include "Mundo.h"
#include <thread>
#include "UI.h"

#define H_MAX 25.0f
#define H_MIN -10.0f
#define W_MAX 31.5f
#define W_MIN -31.5f

enum Estado { INICIO, JUEGO, FIN, RANKING, CARGAR, MODO_LOCAL, MODO_RED, MODO, COLOR, SERVIDOR, CLIENTE, FALLO_CONEXION, PAUSA, COLOR_SERVIDOR};

class CoordinadorAjedrez
{
protected:
	Estado estado;

public:
	Mundo motorGrafico;

	bool inicializarPartida;

	std::thread* motor = new std::thread;

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

float aCoordenadasGlutX(float p);

float aCoordenadasGlutY(float p);

void escrituraGlut(PantallaBase pb,float x,float y);

void aniadirTeclaSuprimir(PantallaBase &pb, unsigned char key);

void borrar(PantallaBase &pb, unsigned char key);