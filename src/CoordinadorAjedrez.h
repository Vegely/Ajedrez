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
	/* MOTORES LÓGICO Y GRÁFICO */
	Mundo mundoGrafico;
	MotorDeJuego motorLogico;
	std::thread* motor = new std::thread;
	/* VARIABLES DE GESTIÓN DE INICIALIZACIÓN Y FINALIZACIÓN */
	bool inicializarPartida;
	DatosFinal datosFinal;

public:
	/* FORMA CANÓNICA */
	CoordinadorAjedrez(void);

	/* FUNCIONES PARA CALLBACKS */
	void initGraficos(void) { mundoGrafico.init(); }
	void Draw(void);
	void Timer(int value);
	void Keypress(unsigned char key);
	void Keylift (unsigned char key);
	void SpecialKeypress(int key);
	void Click(int button, int state, int x, int y);
	
	/* COORDINACIÓN LÓGICA - GRÁFICOS */
	void comunicacionLogicaGraficos(void);
};

#endif