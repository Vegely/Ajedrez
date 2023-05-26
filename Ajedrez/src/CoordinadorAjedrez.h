#pragma once
#include "MotorDeJuego.h"
#include "Mundo.h"
#include <thread>


enum Estado { INICIO, JUEGO, FIN };

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
