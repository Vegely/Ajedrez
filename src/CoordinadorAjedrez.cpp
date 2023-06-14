#include "CoordinadorAjedrez.h"
#include <thread>

ConfiguracionDeJuego configuracion;

void threadMotor(MotorDeJuego* motor, const Mundo& motorGrafico, const ConfiguracionDeJuego* p_configuracion, DatosFinal* p_datosFinal)
{
	//MotorDeJuego motor(*p_configuracion);
	
	for (ConfiguracionDeJuego::FormasDeInteraccion config : p_configuracion->config) 
		if (config == ConfiguracionDeJuego::FormasDeInteraccion::IA) { srand(time(NULL)); break; }

	*p_datosFinal = motor->motor(motorGrafico);

	motor->liberar();
}

CoordinadorAjedrez::CoordinadorAjedrez() :
	estado(INICIO),
	mundoGrafico(),
	motorLogico(configuracion),
	inicializarPartida(true),
	datosFinal()
{ }

void CoordinadorAjedrez::Draw(void)
{
	mundoGrafico.updateCamara();
	mundoGrafico.renderizarModelos();
}

void CoordinadorAjedrez::Timer(int value)
{
	if (estado == JUEGO && inicializarPartida) // Escribir a continuacion de la configuracion
	{
		motor = new std::thread(threadMotor, &this->motorLogico, this->mundoGrafico, &configuracion, &this->mundoGrafico, &this->datosFinal);
		inicializarPartida = false;
	}

	comunicacionLogicaGraficos();
	mundoGrafico.movimiento(value);
}

void CoordinadorAjedrez::Keypress(unsigned char key) 
{
	mundoGrafico.keypress(key);
}

void CoordinadorAjedrez::Keylift(unsigned char key)
{

}

void CoordinadorAjedrez::SpecialKeypress(int key)
{
	
}

void CoordinadorAjedrez::Click(int button, int state, int x, int y)
{
	this->mundoGrafico.seleccionCasilla(button, state, x, y);
}

void CoordinadorAjedrez::comunicacionLogicaGraficos(void)
{
	this->mundoGrafico.dibujarTablero(*this->motorLogico.getTablero());
}