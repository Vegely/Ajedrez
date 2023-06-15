#include "CoordinadorAjedrez.h"
#include <ETSIDI.h>
#include <thread>

ConfiguracionDeJuego configuracion;

PantallaElegirRol pantallaElegirRol;
PantallaInicio pantallaInicio;
PantallaJugadorLocal pantallaJugadorLocal;
PantallaModoDeJuego pantallaModoJuego;
PantallaColorJugador pantallaColorJugador;
PantallaFalloConexion pantallaFalloConexion;
PantallaFinPartida pantallaFinPartida;
PantallaCliente pantallaCliente;
PantallaPausa pantallaPausa;
PantallaServidor pantallaServidor;
PantallaCargarPartida pantallaCargarPartida;
PantallaRankings pantallaRanking;

void threadMotor(const ConfiguracionDeJuego* p_configuracion, Mundo* p_motorGrafico, DatosFinal* p_datosFinal)
{
	MotorDeJuego motor(*p_configuracion);
	
	for (ConfiguracionDeJuego::FormasDeInteraccion config : p_configuracion->config) 
			if (config == ConfiguracionDeJuego::FormasDeInteraccion::IA) { srand(time(NULL)); break; }

	*p_datosFinal = motor.motor();

	motor.liberar();
}

CoordinadorAjedrez::CoordinadorAjedrez() {
	estado=INICIO;
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

	gluLookAt(0, 7.5, 30, // posicion del ojo
		0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

	if (estado == INICIO) {
		
		pantallaInicio.dibuja();
	}
	else if (estado == JUEGO) {
	
	}
	else if (estado == COLOR_SERVIDOR)
	{
		pantallaElegirRol.dibuja();
	}
	else if (estado == MODO_LOCAL)
	{
		pantallaJugadorLocal.dibuja();
	}
	
	else if (estado == MODO)
	{
		pantallaModoJuego.dibuja();
	}
	
	else if (estado == COLOR)
	{
		pantallaColorJugador.dibuja();
	}

	else if (estado == FALLO_CONEXION)
	{
		pantallaFalloConexion.dibuja();
	}

	else if (estado == FIN)
	{
		pantallaFinPartida.dibuja();
	}

	else if (estado ==CLIENTE)
	{
		pantallaCliente.dibuja();
	}

	else if (estado ==PAUSA)
	{
		pantallaPausa.dibuja();
	}

	else if (estado ==SERVIDOR)
	{
		pantallaServidor.dibuja();
	}

	else if (estado ==CARGAR)
	{
		pantallaCargarPartida.dibuja();
	}

	else if (estado ==RANKING)
	{
		pantallaRanking.dibuja();
	}

	
	glEnable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);

	glTexCoord3d(0, 1,-0.1); glVertex3f(-31.5, -8,-0.1);
	glTexCoord3d(1, 1,-0.1); glVertex3f(31.5, -8,-0.1);
	glTexCoord3d(1, 0,-0.1); glVertex3f(31.5, 25,-0.1);
	glTexCoord3d(0, 0,-0.1); glVertex3f(-31.5, 25,-0.1);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	ETSIDI::setFont("bin/fuentes/arial.ttf", 30);
	ETSIDI::setTextColor(0, 255, 0);
	ETSIDI::printxy("hola mundo", 1, 1, 1);
}


void CoordinadorAjedrez::tecla(unsigned char key) 
{
	
}

void CoordinadorAjedrez::teclaEspecial(int key)
{
	
}

void CoordinadorAjedrez::click(int button, int state, int x, int y)
{
	float yg=aCoordenadasGlutY(y);
	float xg=aCoordenadasGlutX(x);
	if (estado == INICIO)
	{
		if(pantallaInicio.salir.enCaja(xg,yg))
			exit(0);
		if (pantallaInicio.nuevaPartida.enCaja(xg, yg))
		estado = MODO;
		if (pantallaInicio.cargarPartida.enCaja(xg, yg))
			estado = CARGAR;
		if (pantallaInicio.mostrarRankings.enCaja(xg, yg))
			estado = RANKING;
	}

}

float aCoordenadasGlutX(float p)
{
	return W_MIN + p * ((W_MAX - W_MIN) / (float)glutGet(GLUT_WINDOW_WIDTH));
}

float aCoordenadasGlutY(float p)
{
	return H_MAX - p * ((-H_MIN + H_MAX) / (float)glutGet(GLUT_WINDOW_HEIGHT));
}




