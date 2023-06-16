#include "CoordinadorAjedrez.h"
#include <ETSIDI.h>
#include <thread>

#define TAM_FRASE 10

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
		escrituraGlut(pantallaInicio, 0.0, 0.0);
	}
	else if (estado == JUEGO)
	{
	
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

	else if (estado == PAUSA)
	{
		pantallaPausa.dibuja();

	}

	else if (estado ==SERVIDOR)
	{
		pantallaServidor.dibuja();


		ETSIDI::setFont("fuentes/consola.ttf", 30);
		ETSIDI::setTextColor(0, 255, 255);
		ETSIDI::printxy(servidor->getip().c_str(), 0, 0, 1);
	}

	else if (estado ==CARGAR)
	{
		pantallaCargarPartida.dibuja();
	}

	else if (estado == RANKING)
	{
		pantallaRanking.dibuja();
<<<<<<< Updated upstream
=======
		parametrosTexturasMEstados();
		ETSIDI::setFont("fuentes/consola.ttf", 30);
		ETSIDI::setTextColor(0, 0, 0);
		ranking.print();
>>>>>>> Stashed changes
	}
	else if (estado == MODO_RED) {
		pantallaElegirRol.dibuja();
	}
	/*else if (estado == GUARDAR) {
		pantallaGuardar
	}*/
}


void CoordinadorAjedrez::tecla(unsigned char key) 
{
	if (estado == JUEGO)
		if (key == 'p')
			estado = PAUSA;
}

void CoordinadorAjedrez::teclaEspecial(int key)
{

}

void CoordinadorAjedrez::click(int button, int state, int x, int y)
{
<<<<<<< Updated upstream
	float yg = aCoordenadasGlutY(y);
	float xg = aCoordenadasGlutX(x);
	//std::cout << state << std::endl;
	if (!state)
=======
	float yg=aCoordenadasGlutY(y);
	float xg=aCoordenadasGlutX(x);

	if (estado == INICIO)
>>>>>>> Stashed changes
	{
		if (estado == INICIO)
		{
			if (pantallaInicio.salir.enCaja(xg, yg))
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
			if (pantallaModoJuego.red.enCaja(xg, yg))
				estado = MODO_RED;
			if (pantallaModoJuego.salir.enCaja(xg, yg))
				estado = INICIO;
		}
		else if (estado == MODO_LOCAL)
		{
			if (pantallaJugadorLocal.IAIA.enCaja(xg, yg))
				estado = JUEGO;
			if (pantallaJugadorLocal.jugadorIA.enCaja(xg, yg))
				estado = COLOR;
			if (pantallaJugadorLocal.dosJugadores.enCaja(xg, yg))
				estado = JUEGO;
			if (pantallaJugadorLocal.atras.enCaja(xg, yg))
				estado = MODO;
		}

		else if (estado == MODO_RED)
		{
			if (pantallaElegirRol.cliente.enCaja(xg, yg))
				estado = CLIENTE;
			if (pantallaElegirRol.servidor.enCaja(xg, yg))
				estado = SERVIDOR;
			if (pantallaElegirRol.atras.enCaja(xg, yg))
				estado = MODO;
		}

		else if (estado == COLOR)
		{
			if (pantallaColorJugador.negro.enCaja(xg, yg))
				estado = JUEGO;
			if (pantallaColorJugador.blanco.enCaja(xg, yg))
				estado = JUEGO;
			if (pantallaColorJugador.atras.enCaja(xg, yg))
				estado = MODO_LOCAL;
		}

		else if (estado == CARGAR)
		{

		}

		else if (estado == PAUSA)
		{
			if (pantallaPausa.guardar_y_salir.enCaja(xg, yg));
			if (pantallaPausa.salir_sin_guardar.enCaja(xg, yg))
				estado = INICIO;
		}
		else if (estado == MODO)
		{
			if (pantallaModoJuego.local.enCaja(xg, yg))
				estado = MODO_LOCAL;
		}
		else if (estado == MODO_LOCAL)
		{
			if (pantallaJugadorLocal.IAIA.enCaja(xg, yg))
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
		else if (estado == CLIENTE)
		{
			if(pantallaCliente.atras.enCaja(xg,yg))
				estado=MODO_RED;
		}
	}
	else if (estado == RANKING) {
		if (pantallaRanking.siguiente.enCaja(xg, yg)) {
			ranking.paginaSiguiente();
		}
		if (pantallaRanking.anterior.enCaja(xg, yg)) {
			ranking.paginaAnterior();
		}
		if (pantallaRanking.atras.enCaja(xg, yg)) {
			estado = INICIO;
			ranking.iniPag();
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

void escrituraGlut(PantallaBase pb, float x, float y)
{
	ETSIDI::setFont("bin/fuentes/arial.ttf", 12);
	ETSIDI::setTextColor(0, 255, 0);
	ETSIDI::printxy(pb.texto.c_str(), x, y, 1);
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


void aniadirTeclaSuprimir(PantallaBase& pb, unsigned char key)
{
	if ((int)key == 127)
		pb.texto = "";
	else if (pb.texto.length() < TAM_FRASE)
		pb.texto += key;
}

void borrar(PantallaBase& pb, unsigned char key)
{
		if (key == GLUT_KEY_LEFT) {
			if (pb.texto.length() > 0)
				pb.texto = pb.texto.substr(0, pb.texto.length() - 1);
		}
}



