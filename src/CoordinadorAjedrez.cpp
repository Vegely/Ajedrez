#include "CoordinadorAjedrez.h"
#include <ETSIDI.h>
#include <thread>
#include "UI.h"

ConfiguracionDeJuego configuracion;
UI ui;

void threadMotor(const ConfiguracionDeJuego* p_configuracion, Mundo* p_motorGrafico, DatosFinal* p_datosFinal)
{
	MotorDeJuego motor(*p_configuracion);
	
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
	if (estado == INICIO) {
		
		
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
		ui.pcj.dibuja();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/pantallas/seleccion color.png").id);

		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);

		glTexCoord2d(0, 1); glVertex2f(-31.5, -8);
		glTexCoord2d(1, 1); glVertex2f(31.5, -8);
		glTexCoord2d(1, 0); glVertex2f(31.5, 25);
		glTexCoord2d(0, 0); glVertex2f(-31.5, 25);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

	}
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




