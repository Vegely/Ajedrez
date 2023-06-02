#include "CoordinadorAjedrez.h"

#include <thread>

ConfiguracionDeJuego configuracion;

void threadMotor(const ConfiguracionDeJuego* p_configuracion, Mundo* p_motorGrafico, DatosFinal* p_datosFinal)
{
	MotorDeJuego motor(*p_configuracion, p_motorGrafico);
	
	for (ConfiguracionDeJuego::FormasDeInteraccion config : p_configuracion->config) 
			if (config == ConfiguracionDeJuego::FormasDeInteraccion::IA) { srand(time(NULL)); break; }

	*p_datosFinal = motor.motor();

	motor.liberar();
}

CoordinadorAjedrez::CoordinadorAjedrez() {
	estado = INICIO;
}

void CoordinadorAjedrez::onTimer()
{
	if (estado == JUEGO && inicializarPartida) // Escribir a continuacion de la configuracion
	{
		motor = new std::thread(threadMotor, &configuracion, &motorGrafico, &datosFinal);
		inicializarPartida = false;
	}
}

void CoordinadorAjedrez::dibuja() 
{
	
}

void CoordinadorAjedrez::tecla(unsigned char key) 
{
	
}

void CoordinadorAjedrez::teclaEspecial(int key)
{
	
}

void CoordinadorAjedrez::click(int button, int state, int x, int y)
{
	
}




