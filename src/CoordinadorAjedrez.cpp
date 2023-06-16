#include "CoordinadorAjedrez.h"
#include <thread>

ConfiguracionDeJuego configuracion;

void threadMotor(MotorDeJuego* motorLogico, Mundo* motorGrafico, const ConfiguracionDeJuego* p_configuracion, DatosFinal* p_datosFinal)
{
	std::cout << "Thread inicializado" << std::endl;
	
	for (ConfiguracionDeJuego::FormasDeInteraccion config : p_configuracion->config) 
		if (config == ConfiguracionDeJuego::FormasDeInteraccion::IA) { srand(time(NULL)); break; }

	*p_datosFinal = motorLogico->motor(motorGrafico);

	motorLogico->liberar();
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
	static bool flag_coronacion = true;

	//if (motorLogico.getTablero()->getTurno() && mundoGrafico.getGirado())
	//{
	//	mundoGrafico.setCamaraPos(Camara::white_pov);
	//	mundoGrafico.cambiarGirado();
	//}
	//else if (!motorLogico.getTablero()->getTurno() && !mundoGrafico.getGirado())
	//{
	//	mundoGrafico.setCamaraPos(Camara::black_pov);
	//	mundoGrafico.cambiarGirado();
	//}

	mundoGrafico.updateCamara();

	if (mundoGrafico.getCoronando() && flag_coronacion)
	{
		mundoGrafico.generarModelosCoronacion(motorLogico.getTablero()->getTurno());
		flag_coronacion = false;
	}
	if (!mundoGrafico.getCoronando())
	{
		mundoGrafico.renderizarModelos();
		flag_coronacion = true;
	}
	else
		mundoGrafico.renderModelosCoronacion(motorLogico.getTablero()->getTurno());
}

// CAMBIAR INICIO POR JUEGO
void CoordinadorAjedrez::Timer(int value)
{
	if (estado == INICIO && inicializarPartida && !flagDeSeguridadInit) // Escribir a continuacion de la configuracion
	{
		motor = new std::thread(threadMotor, &motorLogico, &mundoGrafico, &configuracion, &datosFinal);
		inicializarPartida = false;
	}

	this->mundoGrafico.leerTablero(*this->motorLogico.getTablero());

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
	if (this->mundoGrafico.getCoronando())
		this->mundoGrafico.seleccionCoronacion(button, state, x, y, this->motorLogico.getTablero()->getTurno());
}