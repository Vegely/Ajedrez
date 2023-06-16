#ifndef COORDINADORAJEDREZ_H
#define COORDINADORAJEDREZ_H

#include "MotorDeJuego.h"
#include "Mundo.h"
#include <thread>

enum Estado { INICIO, JUEGO, FIN };

void threadMotor(MotorDeJuego* motorLogico, Mundo* motorGrafico, const ConfiguracionDeJuego* p_configuracion, DatosFinal* p_datosFinal);

class CoordinadorAjedrez
{	
	friend class menuInicial;
private:
	/* ESTADO DEL JUEGO */
	Estado estado;
	/* MOTORES LÓGICO Y GRÁFICO */
	Mundo mundoGrafico;
	MotorDeJuego motorLogico;
	std::thread* motor = nullptr;
	/* VARIABLES DE GESTIÓN DE INICIALIZACIÓN Y FINALIZACIÓN */
	bool inicializarPartida;
	bool flagDeSeguridadInit = true;
	DatosFinal datosFinal;
	
public:
	/* FORMA CANÓNICA */
	CoordinadorAjedrez(void);

	/* FUNCIONES PARA CALLBACKS */
	void initGraficos(void) { mundoGrafico.init(); flagDeSeguridadInit = false; }
	void Draw(void);
	void Timer(int value);
	void Keypress(unsigned char key);
	void Keylift (unsigned char key);
	void SpecialKeypress(int key);
	void Click(int button, int state, int x, int y);
};

#endif