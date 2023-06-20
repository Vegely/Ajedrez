#include "CoordinadorAjedrez.h"
#include <ETSIDI.h>

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
PantallaGuardar pantallaGuardar;

void threadMotor(MotorDeJuego* motorLogico, Mundo* motorGrafico, const ConfiguracionDeJuego* p_configuracion, DatosFinal* p_datosFinal)
{
	std::cout << "Thread inicializado" << std::endl;

	*p_datosFinal = motorLogico->motor(motorGrafico);

	motorLogico->liberar();

	delete motorLogico;
	motorLogico = nullptr;
}

CoordinadorAjedrez::CoordinadorAjedrez() :
	estado(INICIO),
	mundoGrafico(),
	datosFinal()
{}

void hiloServidor(CoordinadorAjedrez* ajedrez) {
	ajedrez->servidor->conectarServidor();
	ajedrez->config = { ConfiguracionDeJuego::FormasDeInteraccion::RECEPTOR, ConfiguracionDeJuego::FormasDeInteraccion::EMISOR, ajedrez->servidor };
	ajedrez->estado = INICIALIZACION_PARTIDA;
}
void hiloCliente(CoordinadorAjedrez* ajedrez) {
	ajedrez->cliente->conectarCliente();
	ajedrez->config = { ConfiguracionDeJuego::FormasDeInteraccion::EMISOR, ConfiguracionDeJuego::FormasDeInteraccion::RECEPTOR, ajedrez->cliente };
	ajedrez->estado = INICIALIZACION_PARTIDA;
}

void CoordinadorAjedrez::Draw(void)
{
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)

	if (estado == INICIO) {
		
		pantallaInicio.dibuja();
		parametrosTexturasMEstados();
	}
	else if (estado == JUEGO)
	{
		mundoGrafico.antisolapamientoCasillas(*p_motorLogico->getTablero());
		mundoGrafico.updateCamara();
		mundoGrafico.renderizarModelos();

		if (datosFinal.finalizada)
		{
			ETSIDI::setFont(RUTA_FUENTES, 30);
			ETSIDI::setTextColor(255, 255, 255);
			ETSIDI::printxy("Pulsa k para continuar", X_FIN, Y_FIN - 5);
			switch (datosFinal.codigoFinal) {
			case CodigoFinal::JAQUE_MATE:
				if(datosFinal.ganaBlanco)
					ETSIDI::printxy("JAQUE MATE BLANCO", X_FIN, Y_FIN);
				else ETSIDI::printxy("JAQUE MATE NEGRAS", X_FIN, Y_FIN);
				break;
			case CodigoFinal::REY_AHOGADO:
				ETSIDI::printxy("REY AHOGADO", X_FIN, Y_FIN);
				break;
			case CodigoFinal::TABLAS_POR_MATERIAL_INSUFICIENTE:
				ETSIDI::printxy("TABLAS POR MATERIAL INSUFICIENTE", X_FIN, Y_FIN);
				break;
			case CodigoFinal::TABLAS_POR_REPETICION:
				ETSIDI::printxy("TABLAS POR REPETICION", X_FIN, Y_FIN);
				break;
			case CodigoFinal::TABLAS_POR_PASIVIDAD:
				ETSIDI::printxy("TABLAS POR PASIVIDAD", X_FIN, Y_FIN);
				break;
			}
		}
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

	else if (estado == PAUSA)
	{
		pantallaPausa.dibuja();
		parametrosTexturasMEstados();
	}

	else if (estado == SERVIDOR)
	{
		pantallaServidor.dibuja();
		parametrosTexturasMEstados();

		ETSIDI::setFont(RUTA_FUENTES, 30);
		ETSIDI::setTextColor(0, 255, 255);
		ETSIDI::printxy(servidor->getip().c_str(), 0, 0, 1);
	}

	else if (estado == CARGAR)
	{
		pantallaCargarPartida.dibuja();
		parametrosTexturasMEstados();
	}

	else if (estado == RANKING)
	{
		pantallaRanking.dibuja();
		parametrosTexturasMEstados();
		ETSIDI::setFont(RUTA_FUENTES, 30);
		ETSIDI::setTextColor(0, 0, 0);
		ranking.print();
	}
	else if (estado == MODO_RED) {
		pantallaElegirRol.dibuja();
		parametrosTexturasMEstados();
	}
	else if (estado == GUARDAR) {
		pantallaGuardar.dibuja();
		parametrosTexturasMEstados();
		pantallaGuardar.escrituraGlut();
	}
	else if (estado == FIN) {
		pantallaFinPartida.dibuja();
		parametrosTexturasMEstados();
	}
}

void CoordinadorAjedrez::Timer(float value)
{
	if (estado == INICIALIZACION_PARTIDA && !flagDeSeguridadInit)
	{
		p_motorLogico = new MotorDeJuego(config, &partida);
		p_motor = new std::thread(threadMotor, p_motorLogico, &mundoGrafico, &configuracion, &datosFinal);
		mundoGrafico.inicializarDesdeTablero(p_motorLogico->getTablero());
		estado = JUEGO;
	}
	else if (estado == JUEGO) // Escribir a continuacion de la configuracion
	{	
		this->p_motorLogico->comprobarCasillasJaque(&this->motorGrafico);
		this->mundoGrafico.leerTablero(*this->p_motorLogico->getTablero());
		this->mundoGrafico.actualizarCamara(this->p_motorLogico->getTablero()->getTurno(), value);
		this->mundoGrafico.movimiento(value);
	}
}

void CoordinadorAjedrez::Keypress(unsigned char key) 
{
	if (estado == GUARDAR)
	{
		if ((int)key == SUPRIMIR) {
			if (pantallaGuardar.estado == Guardar::PARTIDA)
				pantallaGuardar.snombre_partida = "";
			else if (pantallaGuardar.estado == Guardar::BLANCAS)
				pantallaGuardar.sblancas = "";
			else if (pantallaGuardar.estado == Guardar::NEGRAS)
				pantallaGuardar.snegras = "";
		}
		else if ((int)key == TABULADOR) {
			std::string fin = CARPETA_NOFINALIZADAS;
			if (datosFinal.finalizada)fin = CARPETA_FINALIZADAS;
			partida.setNombre(fin + pantallaGuardar.snombre_partida + ".txt");
			if (partida.existe())
				pantallaGuardar.existe = 1;
			else
			{
				estado = INICIO;

				//Actualización de la partida
				partida.setFin(datosFinal.finalizada);
				partida.setBlancas(pantallaGuardar.sblancas);
				partida.setNegras(pantallaGuardar.snegras);
				partida.setModo(pantallaGuardar.smodo);
				partida.crearPartida();
				partida.guardarPartida();

				//Actualización del ranking
				ranking.aniadirJugador(pantallaGuardar.sblancas);
				ranking.aniadirJugador(pantallaGuardar.snegras);

				if (datosFinal.finalizada) {
					if (datosFinal.codigoFinal == CodigoFinal::JAQUE_MATE) {
						if (datosFinal.ganaBlanco) {
							ranking.actualizar(pantallaGuardar.sblancas, 3.0);
							ranking.actualizar(pantallaGuardar.snegras, -3.0);
						}
						else {
							ranking.actualizar(pantallaGuardar.sblancas, -3.0);
							ranking.actualizar(pantallaGuardar.snegras, 3.0);
						}
					}
					else {
						ranking.actualizar(pantallaGuardar.sblancas, 1.0);
						ranking.actualizar(pantallaGuardar.snegras, 1.0);
					}
				}

				//Reset a valores iniciales para guardar futuras partidas
				partida.reset();
				pantallaGuardar.reset();
			}
		}
		else {
			if (pantallaGuardar.estado == Guardar::PARTIDA && pantallaGuardar.snombre_partida.length() < TAM_FRASE)
				pantallaGuardar.snombre_partida += key;
			else if (pantallaGuardar.estado == Guardar::BLANCAS && pantallaGuardar.sblancas.length() < TAM_FRASE && pantallaGuardar.sblancas!=JIA)
				pantallaGuardar.sblancas += key;
			else if (pantallaGuardar.estado == Guardar::NEGRAS && pantallaGuardar.snegras.length() < TAM_FRASE && pantallaGuardar.snegras!=JIA)
				pantallaGuardar.snegras += key;
		}
	}
	else if (estado == JUEGO) {
		if (key == 'p')
			estado = PAUSA;
		///////////////////////////////////////////
		//Falta resetear valores
		else if (datosFinal.finalizada == true && key == 'k')
		{
			estado = FIN;
			p_motor->join();
		}
		/////////////////////////////////////////
	}
	else if (estado == PAUSA) {
		if (key == 'c')
			estado = JUEGO;
	}
}

void CoordinadorAjedrez::Keylift(unsigned char key)
{

}

void CoordinadorAjedrez::SpecialKeypress(int key)
{
	if (estado == GUARDAR) {
		if (key == GLUT_KEY_LEFT) {
			if (pantallaGuardar.estado == Guardar::PARTIDA && pantallaGuardar.snombre_partida.length() > 0)
				pantallaGuardar.snombre_partida = pantallaGuardar.snombre_partida.substr(0, pantallaGuardar.snombre_partida.length() - 1);

			else if (pantallaGuardar.estado == Guardar::BLANCAS && pantallaGuardar.sblancas.length() > 0)
				pantallaGuardar.sblancas = pantallaGuardar.sblancas.substr(0, pantallaGuardar.sblancas.length() - 1);

			else if (pantallaGuardar.estado == Guardar::NEGRAS && pantallaGuardar.snegras.length() > 0)
				pantallaGuardar.snegras = pantallaGuardar.snegras.substr(0, pantallaGuardar.snegras.length() - 1);
		}
	}
	else if (estado == JUEGO) {
		if (key == 27)
			estado = PAUSA;
	}
}

void CoordinadorAjedrez::Click(int button, int state, int x, int y)
{
	float yg=aCoordenadasGlutY(y);
	float xg=aCoordenadasGlutX(x);

	if (!state) {
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
		else if (estado == JUEGO) {
			this->mundoGrafico.seleccionCasilla(button, state, x, y);
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
			{
				pantallaGuardar.smodo = IA_IA;
				pantallaGuardar.sblancas = JIA;
				pantallaGuardar.snegras = JIA;
				config = {ConfiguracionDeJuego::FormasDeInteraccion::IA, ConfiguracionDeJuego::FormasDeInteraccion::IA };
				estado = INICIALIZACION_PARTIDA;
			}
			if (pantallaJugadorLocal.jugadorIA.enCaja(xg, yg))
			{
				pantallaGuardar.smodo = LOCAL_IA;
				estado = COLOR;
			}
			if (pantallaJugadorLocal.dosJugadores.enCaja(xg, yg))
			{
				pantallaGuardar.smodo = LOCAL_LOCAL;
				config = { ConfiguracionDeJuego::FormasDeInteraccion::LOCAL, ConfiguracionDeJuego::FormasDeInteraccion::LOCAL };
				estado = INICIALIZACION_PARTIDA;
			}
			if (pantallaJugadorLocal.atras.enCaja(xg, yg))
				estado = MODO;
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
		else if (estado == COLOR)
		{
			if (pantallaColorJugador.negro.enCaja(xg, yg))
			{
				pantallaGuardar.sblancas = JIA;
				config = { ConfiguracionDeJuego::FormasDeInteraccion::LOCAL, ConfiguracionDeJuego::FormasDeInteraccion::IA };
				estado = INICIALIZACION_PARTIDA;
			}
			if (pantallaColorJugador.blanco.enCaja(xg, yg))
			{
				pantallaGuardar.snegras = JIA;
				config = { ConfiguracionDeJuego::FormasDeInteraccion::IA, ConfiguracionDeJuego::FormasDeInteraccion::LOCAL };
				estado = INICIALIZACION_PARTIDA;
			}
			if (pantallaColorJugador.atras.enCaja(xg, yg))
				estado = MODO_LOCAL;
		}
		else if (estado == PAUSA)
		{
			if (pantallaPausa.guardar_y_salir.enCaja(xg, yg))
			{
				estado = GUARDAR;
				p_motorLogico->setExit(true);
			}
			if (pantallaPausa.salir_sin_guardar.enCaja(xg, yg))
			{
				estado = INICIO;
				p_motorLogico->setExit(true);
			}
		}
		else if (estado == CLIENTE)
		{
			if (pantallaCliente.atras.enCaja(xg, yg))
			{
				estado = MODO_RED;
				cliente->desconectarCliente();
				hilo_cliente->join();
			}
		}
		else if (estado == SERVIDOR) {
			if (pantallaServidor.atras.enCaja(xg, yg))
			{
				estado = MODO_RED;
				servidor->desconectarServidor();
				hilo_servidor->join();
			}
		}
		else if (estado == CARGAR) {
			if (pantallaCargarPartida.atras.enCaja(xg, yg))
				estado = INICIO;
		}
		else if (estado == GUARDAR) {
			if (pantallaGuardar.nombre_partida.enCaja(xg, yg))
			{
				if (pantallaGuardar.existe)
				{
					pantallaGuardar.existe = 0;
					pantallaGuardar.snombre_partida = "";
				}
				pantallaGuardar.estado = Guardar::PARTIDA;
			}
			else if (pantallaGuardar.blancas.enCaja(xg, yg))
				pantallaGuardar.estado = Guardar::BLANCAS;
			else if (pantallaGuardar.negras.enCaja(xg, yg))
				pantallaGuardar.estado = Guardar::NEGRAS;
			else pantallaGuardar.estado = Guardar::NONE;
		}
		else if (estado == FIN) {
			if (pantallaFinPartida.guardar_y_salir.enCaja(xg, yg)) estado = GUARDAR;
			else if (pantallaFinPartida.salir_sin_guardar.enCaja(xg, yg)) estado = INICIO;
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
