#ifndef COORDINADORAJEDREZ_H
#define COORDINADORAJEDREZ_H

#include "MotorDeJuego.h"
#include "Mundo.h"
#include <thread>

enum Estado { INICIO, JUEGO, FIN };

void threadMotor(MotorDeJuego* motor, const Mundo& p_motorGrafico, const ConfiguracionDeJuego* p_configuracion, DatosFinal* p_datosFinal);

class CoordinadorAjedrez
{	
	friend class menuInicial;
private:
	/* ESTADO DEL JUEGO */
	Estado estado;
	/* MOTORES L�GICO Y GR�FICO */
	Mundo mundoGrafico;
	MotorDeJuego motorLogico;
	std::thread* motor = new std::thread;
	/* VARIABLES DE GESTI�N DE INICIALIZACI�N Y FINALIZACI�N */
	bool inicializarPartida;
	DatosFinal datosFinal;

public:
	/* FORMA CAN�NICA */
	CoordinadorAjedrez(void);

	/* FUNCIONES PARA CALLBACKS */
	void initGraficos(void) { mundoGrafico.init(); }
	void Draw(void);
	void Timer(int value);
	void Keypress(unsigned char key);
	void Keylift (unsigned char key);
	void SpecialKeypress(int key);
	void Click(int button, int state, int x, int y);
	
	/* COORDINACI�N L�GICA - GR�FICOS */
	void comunicacionLogicaGraficos(void);
};

#endif