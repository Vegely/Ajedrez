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

void hiloServidor(CoordinadorAjedrez* ajedrez) {
	ajedrez->servidor->conectarServidor();
}
void hiloCliente(CoordinadorAjedrez* ajedrez) {
	ajedrez->cliente->conectarCliente();
}

CoordinadorAjedrez::CoordinadorAjedrez() {
	estado=MODO_RED;
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
		parametrosTexturasMEstados();
	}
	else if (estado == JUEGO) {
	
	}
	else if (estado == COLOR_SERVIDOR)
	{
		pantallaElegirRol.dibuja();
		parametrosTexturasMEstados();
	}
	else if (estado == MODO_LOCAL)
	{
		pantallaJugadorLocal.dibuja();
		parametrosTexturasMEstados();
	}
	
	else if (estado == MODO)
	{
		pantallaModoJuego.dibuja();
		parametrosTexturasMEstados();
	}
	
	else if (estado == COLOR)
	{
		pantallaColorJugador.dibuja();
		parametrosTexturasMEstados();
	}

	else if (estado == FALLO_CONEXION)
	{
		pantallaFalloConexion.dibuja();
		parametrosTexturasMEstados();
	}

	else if (estado == FIN)
	{
		pantallaFinPartida.dibuja();
		parametrosTexturasMEstados();
	}

	else if (estado ==CLIENTE)
	{
		pantallaCliente.dibuja();
		parametrosTexturasMEstados();
	}

	else if (estado ==PAUSA)
	{
		pantallaPausa.dibuja();
		parametrosTexturasMEstados();
	}

	else if (estado ==SERVIDOR)
	{
		pantallaServidor.dibuja();
		parametrosTexturasMEstados();

		ETSIDI::setFont("fuentes/arial.ttf", 30);
		ETSIDI::setTextColor(0, 255, 255);
		ETSIDI::printxy(servidor->getip().c_str(), 0, 0, 1);
	}

	else if (estado ==CARGAR)
	{
		pantallaCargarPartida.dibuja();
		parametrosTexturasMEstados();
	}

	else if (estado ==RANKING)
	{
		pantallaRanking.dibuja();
		parametrosTexturasMEstados();
	}
	else if (estado == MODO_RED) {
		pantallaElegirRol.dibuja();
		parametrosTexturasMEstados();
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
	else if (estado == MODO)
	{
		if (pantallaModoJuego.local.enCaja(xg, yg))
			estado = MODO_LOCAL;
	}
	else if (estado == MODO_LOCAL)
	{
		if (pantallaJugadorLocal.IAIA.enCaja(xg,yg))
			estado == JUEGO;
		if (pantallaJugadorLocal.jugadorIA.enCaja(xg, yg))
			estado == COLOR;
		if (pantallaJugadorLocal.dosJugadores.enCaja(xg, yg))
			estado == JUEGO;
	}
	else if (estado == MODO_RED) {
		if (pantallaElegirRol.atras.enCaja(xg, yg))
			estado = MODO;
		if (pantallaElegirRol.cliente.enCaja(xg, yg)) {
			estado = CLIENTE;
			inicializaWinSock();
			cliente = new Cliente;
			cliente->inicializa();
			hilo_cliente = new std::thread(hiloCliente, this);

		}
		if (pantallaElegirRol.servidor.enCaja(xg, yg)) {
			estado = SERVIDOR;
			inicializaWinSock();
			servidor = new Servidor;
			servidor->inicializa();
			hilo_servidor = new std::thread(hiloServidor, this);
		}
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

void parametrosTexturasMEstados()
{
	glEnable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);

	glTexCoord3d(0, 1, -0.1); glVertex3f(-31.5, -8, -0.1);
	glTexCoord3d(1, 1, -0.1); glVertex3f(31.5, -8, -0.1);
	glTexCoord3d(1, 0, -0.1); glVertex3f(31.5, 25, -0.1);
	glTexCoord3d(0, 0, -0.1); glVertex3f(-31.5, 25, -0.1);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}


