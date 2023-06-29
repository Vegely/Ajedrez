#define _USE_MATH_DEFINES
#include "CoordinadorAjedrez.h"
#include <ETSIDI.h>
#include <cmath>

#include "Plane.h"

#include <thread>
#include <chrono>
#include <filesystem>

#include "Sonidos.h"
PantallaElegirRol	  pantallaElegirRol;
PantallaInicio		  pantallaInicio;
PantallaJugadorLocal  pantallaJugadorLocal;
PantallaModoDeJuego   pantallaModoJuego;
PantallaColorJugador  pantallaColorJugador;
PantallaFalloConexion pantallaFalloConexion;
PantallaFinPartida	  pantallaFinPartida;
PantallaCliente		  pantallaCliente;
PantallaPausa		  pantallaPausa;
PantallaServidor	  pantallaServidor;
PantallaCargarPartida pantallaCargarPartida;
PantallaRankings	  pantallaRanking;
PantallaGuardar		  pantallaGuardar;

void threadMotor(bool* p_run, Mundo* p_motorGrafico, const ConfiguracionDeJuego* p_config, Partida* p_partida, ElementoRed* p_elementoRed, DatosFinal* p_datosFinal)
{
	MotorDeJuego motor(p_config, p_partida, p_elementoRed);

	*p_datosFinal = motor.motor(p_motorGrafico, *p_run);

	motor.liberar();
}

CoordinadorAjedrez::CoordinadorAjedrez() :
	estado(INICIO),
	motorGrafico(),
	datosFinal()
{}

void hiloRed(CoordinadorAjedrez* p_ajedrez)
{
	bool con = p_ajedrez->p_elementoRed->conectar();
	if (con && p_ajedrez->redAbierta)
	{
		p_ajedrez->estado = INICIALIZAR_PARTIDA;

		int conectado = 1;
		while (conectado > 0 && p_ajedrez->redAbierta) // Hay que a�adir el error en el paquet porque no hay un callback al cerrar la ventana 
			// con la X para avisar al otro extremo de la red de que ha habido una desconexion
		{
			if (p_ajedrez->p_elementoRed->recibido.empty())
				conectado = p_ajedrez->p_elementoRed->recibir(p_ajedrez->p_elementoRed->recibido);
		}
	}

	if (!con || p_ajedrez->redAbierta)
		p_ajedrez->estado = FALLO_CONEXION;
}

void CoordinadorAjedrez::init(void)
{
	motorGrafico.init();
	flagDeSeguridadInit = false;
	pantallaElegirRol.init();
	pantallaInicio.init();
	pantallaJugadorLocal.init();
	pantallaModoJuego.init();
	pantallaColorJugador.init();
	pantallaFalloConexion.init();
	pantallaFinPartida.init();
	pantallaCliente.init();
	pantallaPausa.init();
	pantallaServidor.init();
	pantallaCargarPartida.init();
	pantallaRanking.init();
	pantallaGuardar.init();
}

void CoordinadorAjedrez::gestionSonido()
{
	static bool sonidoMenuInicializado = false;
	static bool sonidoJuegoInicializado = false;
	if (estado != JUEGO)
	{
		sonidoJuegoInicializado = false;
		if (!sonidoMenuInicializado)
		{
			sonidoMenuInicializado = true;
			Sonidos::mus_menu();
		}
	}
	else
	{
		sonidoMenuInicializado = false;
		if (!sonidoJuegoInicializado)
		{
			sonidoJuegoInicializado = true;
			Sonidos::mus_juego();
		}
	}
}
void CoordinadorAjedrez::Draw(void)
{
	static bool iniciaSonidoFinal=false;
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0.0, 7.5, 0.0,    // hacia que punto mira 
		0.0, 1.0, 0.0);   // definimos hacia arriba (eje Y)
	gestionSonido();

	if (estado == INICIALIZAR_PARTIDA)
	{
		motorGrafico.getCasillaJaque()->renderModelos();
		motorGrafico.getCasillaUltimoMov()->renderModelos();
	}
	else if (estado == INICIO) {

		pantallaInicio.dibuja();
		parametrosTexturasMEstados();
	}
	else if (estado == JUEGO)
	{
		motorGrafico.updateCamara();
		motorGrafico.renderizarModelos();
		 

		if (datosFinal.finalizada)
		{
			Sonidos::mus_fin();
			switch (datosFinal.codigoFinal)
			{
			case CodigoFinal::JAQUE_MATE:
				if (datosFinal.ganaBlanco)
				{
					renderPantallaTransparente(RUTA_JAQUE_MATE_BLANCAS, motorGrafico.getCamaraAng());
				}
				else
				{
					renderPantallaTransparente(RUTA_JAQUE_MATE_NEGRAS, motorGrafico.getCamaraAng());
				}
				///
				if(!iniciaSonidoFinal)
					Sonidos::son_jaquemate();
				///
				break;

			case CodigoFinal::REY_AHOGADO:
				renderPantallaTransparente(RUTA_REY_AHOGADO, motorGrafico.getCamaraAng());
				///
				if (!iniciaSonidoFinal)
					Sonidos::son_tablas();
				///
				break;

			case CodigoFinal::TABLAS_POR_MATERIAL_INSUFICIENTE:
				renderPantallaTransparente(RUTA_MATERIAL_INSUFICIENTE, motorGrafico.getCamaraAng());
				///
				if (!iniciaSonidoFinal)
					Sonidos::son_tablas();
				///
				break;

			case CodigoFinal::TABLAS_POR_REPETICION:
				renderPantallaTransparente(RUTA_REPETICION, motorGrafico.getCamaraAng());
				///
				if (!iniciaSonidoFinal)
					Sonidos::son_tablas();
				///
				break;

			case CodigoFinal::TABLAS_POR_PASIVIDAD:
				renderPantallaTransparente(RUTA_PASIVIDAD, motorGrafico.getCamaraAng());
				///
				if (!iniciaSonidoFinal)
					Sonidos::son_tablas();
				///
				break;
			}
			iniciaSonidoFinal = true;
		}
		else
			iniciaSonidoFinal = false;
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

	else if (estado == CLIENTE)
	{
		pantallaCliente.dibuja();
		parametrosTexturasMEstados();

		ETSIDI::setFont(RUTA_FUENTES, 30);
		ETSIDI::setTextColor(0, 255, 255);
		ETSIDI::printxy(pantallaCliente.ip.c_str(), -6, 7, 1);
	}

	else if (estado == PAUSA)
	{
		motorGrafico.updateCamara();
		motorGrafico.renderizarModelos();
		renderPantallaTransparente(RUTA_PAUSA, motorGrafico.getCamaraAng());
	}

	else if (estado == SERVIDOR)
	{
		pantallaServidor.dibuja();
		parametrosTexturasMEstados();

		ETSIDI::setFont(RUTA_FUENTES, 30);
		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::printxy(p_elementoRed->getIp().c_str(), -6, 7, 1);
	}

	else if (estado == CARGAR)
	{
		pantallaCargarPartida.dibuja();
		parametrosTexturasMEstados();
		pantallaCargarPartida.escrituraGlut();
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
}

void CoordinadorAjedrez::abrirRed()
{
	redAbierta = true;
	p_elementoRed->inicializa();
	p_hilo_elementoRed = new std::thread(hiloRed, this);
}

void CoordinadorAjedrez::cerrarHiloRed()
{
	if (p_hilo_elementoRed != nullptr)
	{
		p_elementoRed->desconectar();

		redAbierta = false;

		p_hilo_elementoRed->join();

		// Se elimina el hilo donde se estaba conectando
		delete p_hilo_elementoRed;
		p_hilo_elementoRed = nullptr;
	}

	// Se elimina el elemento de red
	delete p_elementoRed;
	p_elementoRed = nullptr;

	// Se elimina la frase CONECTANDO de la pantalla del cliente
	pantallaCliente.ip = "";
}

void CoordinadorAjedrez::cerrarPartida()
{
	enPartida = false;

	if (p_hilo_elementoRed != nullptr) cerrarHiloRed();

	// Esperar a que el hilo del motor logico acabe y eliminarlo
	p_hiloMotorLogico->join();

	delete p_hiloMotorLogico;
	p_hiloMotorLogico = nullptr;
}

void CoordinadorAjedrez::Timer(float value)
{
	if (estado == INICIALIZAR_PARTIDA && !flagDeSeguridadInit)
	{
		datosFinal.finalizada = false;
		enPartida = true;
		p_hiloMotorLogico = new std::thread(threadMotor, &(enPartida), &motorGrafico, &config, &partida, p_elementoRed, &datosFinal);

		motorGrafico.resetCasillas(motorGrafico.getCasillaUltimoMov());
		motorGrafico.resetCasillas(motorGrafico.getCasillaJaque());

		estado = JUEGO;
	}
	else if (estado == JUEGO) // Escribir a continuacion de la configuracion
		this->motorGrafico.movimiento(value);
	else if (estado == CERRAR_PARTIDA)
	{
		cerrarPartida();

		estado = INICIO;
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
			if (flag_cargar_partida) 
			{
				if(partida.getNombreCargar() == pantallaGuardar.snombre_partida)
				{

					std::string ruta = (fin + partida.getNombreCargar() + ".txt");
					std::filesystem::remove(ruta);
				}
					
				partida.setNombreCargar("");
			}
			if (datosFinal.finalizada)
				fin = CARPETA_FINALIZADAS;

			partida.setNombre(fin + pantallaGuardar.snombre_partida + ".txt");

			if (partida.existe()&&!flag_cargar_partida)
				pantallaGuardar.existe = 1;
			else
			{
				///
				estado = INICIO;
				///

				//Actualizaci�n de la partida
				partida.setFin(datosFinal.finalizada);
				partida.setBlancas(pantallaGuardar.sblancas);
				partida.setNegras(pantallaGuardar.snegras);
				partida.setModo(pantallaGuardar.smodo);
				partida.crearPartida();
				partida.guardarPartida();

				//Actualizacion del ranking
				ranking.aniadirJugador(pantallaGuardar.sblancas);
				ranking.aniadirJugador(pantallaGuardar.snegras);

				if (datosFinal.finalizada) {
					if (datosFinal.codigoFinal == CodigoFinal::JAQUE_MATE) {
						if (datosFinal.ganaBlanco) {
							ranking.actualizar(pantallaGuardar.sblancas, 3.0);
							ranking.actualizar(pantallaGuardar.snegras, 0.0);
						}
						else {
							ranking.actualizar(pantallaGuardar.sblancas, 0.0);
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

				flag_cargar_partida = false;
				pantallaCargarPartida.pagina_actual = 0;

				estado = CERRAR_PARTIDA;
			}
		}
		else {
			if (pantallaGuardar.estado == Guardar::PARTIDA && pantallaGuardar.snombre_partida.length() < TAM_FRASE)
			{
				if (key >= 'A' && key <= 'Z' || key >= 'a' && key <= 'z' || key >= '0' && key <= '9')
					pantallaGuardar.snombre_partida += key;
			}
			else if (pantallaGuardar.estado == Guardar::BLANCAS && pantallaGuardar.sblancas.length() < TAM_FRASE && pantallaGuardar.sblancas != JIA)
				{
					if (key >= 'A' && key <= 'Z' || key >= 'a' && key <= 'z' || key >= '0' && key <= '9')
						pantallaGuardar.sblancas += key;
				}
			else if (pantallaGuardar.estado == Guardar::NEGRAS && pantallaGuardar.snegras.length() < TAM_FRASE && pantallaGuardar.snegras != JIA)
				{
					if (key >= 'A' && key <= 'Z' || key >= 'a' && key <= 'z' || key >= '0' && key <= '9')
						pantallaGuardar.snegras += key;
				}
		}
	}
	else if (estado == JUEGO) {
		if (key == ESCAPE) // Esc
			estado = PAUSA;

		else if (datosFinal.finalizada == true && key == 'k')
		{
			estado = FIN; 
		}
	}
	else if (estado == PAUSA) {
		if (key == ESCAPE) // Esc
			estado = JUEGO;
	}
	else if (estado == CLIENTE)
	{
		if ((int)key == SUPRIMIR)
			pantallaCliente.ip = "";
		else if ((int)key == TABULADOR)
		{
			p_elementoRed->setIp(pantallaCliente.ip);
			abrirRed();
			pantallaCliente.ip = CONECTANDO;
		}
		else
		{
			if (pantallaCliente.ip.size() < TAM_MAX_IP && ((key >= '0' && key <= '9') || key == '.') && pantallaCliente.ip!=CONECTANDO)
				pantallaCliente.ip += key;
		}
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

			else if (pantallaGuardar.estado == Guardar::BLANCAS && pantallaGuardar.sblancas.length() > 0 && pantallaGuardar.sblancas!=JIA)
				pantallaGuardar.sblancas = pantallaGuardar.sblancas.substr(0, pantallaGuardar.sblancas.length() - 1);

			else if (pantallaGuardar.estado == Guardar::NEGRAS && pantallaGuardar.snegras.length() > 0 && pantallaGuardar.snegras != JIA)
				pantallaGuardar.snegras = pantallaGuardar.snegras.substr(0, pantallaGuardar.snegras.length() - 1);
		}
	}
	else if (estado == CLIENTE) {
		if (key == GLUT_KEY_LEFT) {
			if (pantallaCliente.ip.length() > 0)
				pantallaCliente.ip = pantallaCliente.ip.substr(0, pantallaCliente.ip.length() - 1);
		}
	}
}

void CoordinadorAjedrez::Click(int button, int state, int x, int y)
{
	float yg = aCoordenadasGlutY(y);
	float xg = aCoordenadasGlutX(x);

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
			this->motorGrafico.seleccionCasilla(button, state, x, y);
		}
		else if (estado == MODO)
		{
			if (pantallaModoJuego.local.enCaja(xg, yg))
				estado = MODO_LOCAL;
			if (pantallaModoJuego.red.enCaja(xg, yg))
				estado = MODO_RED;
			if (pantallaModoJuego.atras.enCaja(xg, yg))
				estado = INICIO;
		}
		else if (estado == MODO_LOCAL)
		{
			if (pantallaJugadorLocal.IAIA.enCaja(xg, yg))
			{
				pantallaGuardar.smodo = IA_IA;
				pantallaGuardar.sblancas = JIA;
				pantallaGuardar.snegras = JIA;
				config = { ConfiguracionDeJuego::FormasDeInteraccion::IA, ConfiguracionDeJuego::FormasDeInteraccion::IA };
				estado = INICIALIZAR_PARTIDA;
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
				estado = INICIALIZAR_PARTIDA;
			}
			if (pantallaJugadorLocal.atras.enCaja(xg, yg))
				estado = MODO;
		}
		else if (estado == MODO_RED) {
			if (pantallaElegirRol.atras.enCaja(xg, yg))
				estado = MODO;
			else
			{
				bool cliente = pantallaElegirRol.cliente.enCaja(xg, yg);
				if (cliente || pantallaElegirRol.servidor.enCaja(xg, yg)) // Si se selecciona la caja de cliente o de servidor
				{
					inicializaWinSock();
					if (cliente) // Cliente
					{
						p_elementoRed = new Cliente;
						config = { ConfiguracionDeJuego::FormasDeInteraccion::EMISOR, ConfiguracionDeJuego::FormasDeInteraccion::RECEPTOR };

						estado = CLIENTE;
					}
					else // Servidor
					{
						p_elementoRed = new Servidor;
						config = { ConfiguracionDeJuego::FormasDeInteraccion::RECEPTOR, ConfiguracionDeJuego::FormasDeInteraccion::EMISOR };

						estado = SERVIDOR;

						abrirRed();
					}
				}
			}
		}
		else if (estado == FALLO_CONEXION)
		{
			if (pantallaFalloConexion.aceptar.enCaja(xg, yg))
				estado = CERRAR_PARTIDA;
		}
		else if (estado == RANKING)
		{
			if (pantallaRanking.siguiente.enCaja(xg, yg))
				ranking.paginaSiguiente();
			if (pantallaRanking.anterior.enCaja(xg, yg))
				ranking.paginaAnterior();
			if (pantallaRanking.atras.enCaja(xg, yg))
			{
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
				estado = INICIALIZAR_PARTIDA;
			}
			else if (pantallaColorJugador.blanco.enCaja(xg, yg))
			{
				pantallaGuardar.snegras = JIA;
				config = { ConfiguracionDeJuego::FormasDeInteraccion::IA, ConfiguracionDeJuego::FormasDeInteraccion::LOCAL };
				estado = INICIALIZAR_PARTIDA;
			}
			else if (pantallaColorJugador.atras.enCaja(xg, yg))
				estado = MODO_LOCAL;
		}
		else if (estado == PAUSA)
		{
			if (pantallaPausa.guardar_y_salir.enCaja(xg, yg))
				estado = GUARDAR;
			if (pantallaPausa.salir_sin_guardar.enCaja(xg, yg))
			{
				flag_cargar_partida = false;
				partida.reset();
				pantallaGuardar.reset();
				estado = CERRAR_PARTIDA;
			}
		}
		else if (estado == CLIENTE || estado == SERVIDOR)
		{
			if (pantallaCliente.atras.enCaja(xg, yg))
			{
				cerrarHiloRed();
				estado = MODO_RED;
				pantallaCliente.ip = "";
			}
		}
		else if (estado == CARGAR) {
			if (pantallaCargarPartida.atras.enCaja(xg, yg))
			{
				pantallaCargarPartida.pagina_actual = 0;
				estado = INICIO;
			}
			else if (pantallaCargarPartida.anterior.enCaja(xg, yg))
				pantallaCargarPartida.paginaAnterior();
			else if (pantallaCargarPartida.siguiente.enCaja(xg, yg))
				pantallaCargarPartida.paginaSiguiente();
			else if (pantallaCargarPartida.partida1.enCaja(xg, yg)) {
				if(pantallaCargarPartida.p1_nombre!= CARPETA_NOFINALIZADAS)
				{
					partida.setNombre(pantallaCargarPartida.p1_nombre);
					partida.cargarPartida();
					flag_cargar_partida = true;
					pantallaGuardar.cargarPartida(partida);
					partida.setNombreCargar(pantallaGuardar.snombre_partida);
					estado = INICIALIZAR_PARTIDA;
				}
			}
			else if (pantallaCargarPartida.partida2.enCaja(xg, yg)) {
				if (pantallaCargarPartida.p2_nombre != CARPETA_NOFINALIZADAS)
				{
					partida.setNombre(pantallaCargarPartida.p2_nombre);
					partida.cargarPartida();
					flag_cargar_partida = true;
					pantallaGuardar.cargarPartida(partida);
					partida.setNombreCargar(pantallaGuardar.snombre_partida);
					estado = INICIALIZAR_PARTIDA;
				}
			}
			else if (pantallaCargarPartida.partida3.enCaja(xg, yg)) {
				if (pantallaCargarPartida.p3_nombre != CARPETA_NOFINALIZADAS)
				{
					partida.setNombre(pantallaCargarPartida.p3_nombre);
					partida.cargarPartida();
					flag_cargar_partida = true;
					pantallaGuardar.cargarPartida(partida);
					partida.setNombreCargar(pantallaGuardar.snombre_partida);
					estado = INICIALIZAR_PARTIDA;
				}
			}
			else if (pantallaCargarPartida.partida4.enCaja(xg, yg)) {
				if (pantallaCargarPartida.p4_nombre != CARPETA_NOFINALIZADAS)
				{
					partida.setNombre(pantallaCargarPartida.p4_nombre);
					partida.cargarPartida();
					flag_cargar_partida = true;
					pantallaGuardar.cargarPartida(partida);
					partida.setNombreCargar(pantallaGuardar.snombre_partida);
					estado = INICIALIZAR_PARTIDA;
				}
			}
			else if (pantallaCargarPartida.partida5.enCaja(xg, yg)) {
				if (pantallaCargarPartida.p5_nombre != CARPETA_NOFINALIZADAS)
				{
					partida.setNombre(pantallaCargarPartida.p5_nombre);
					partida.cargarPartida();
					flag_cargar_partida = true;
					pantallaGuardar.cargarPartida(partida);
					partida.setNombreCargar(pantallaGuardar.snombre_partida);
					estado = INICIALIZAR_PARTIDA;
				}
			}
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
			else if (pantallaFinPartida.salir_sin_guardar.enCaja(xg, yg)) estado = CERRAR_PARTIDA;
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

void CoordinadorAjedrez::renderPantallaTransparente(const std::string& filepath, float main_ang, const Point& pos, float rot_x, float rot_y, float rot_z)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(filepath.c_str()).id);

	Plane screen(10.8f * 2.0f, 19.2f * 2.0f, Point::zero, "Plane");
	screen.rotate('y', rot_y, screen.getPosition());
	screen.rotate('z', rot_z, screen.getPosition());
	screen.setPosition(pos);
	screen.rotate('x', -rot_x, Point::zero);

	screen.rotate('y', -main_ang * 180.0f / M_PI - 90.0f, Point::zero);

	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	{
		glTexCoord3d(1, 1, -0.1); glVertex3f(screen.getCornersPosition().ll.x, screen.getCornersPosition().ll.y, screen.getCornersPosition().ll.z);
		glTexCoord3d(1, 0, -0.1); glVertex3f(screen.getCornersPosition().lr.x, screen.getCornersPosition().lr.y, screen.getCornersPosition().lr.z);
		glTexCoord3d(0, 0, -0.1); glVertex3f(screen.getCornersPosition().ur.x, screen.getCornersPosition().ur.y, screen.getCornersPosition().ur.z);
		glTexCoord3d(0, 1, -0.1); glVertex3f(screen.getCornersPosition().ul.x, screen.getCornersPosition().ul.y, screen.getCornersPosition().ul.z);
	}
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void debugAxis(void)
{
	// Debug: reference axis:
	glTranslatef(25000, 25000, 25000);
	glColor3f(255, 255, 255);
	glutWireCube(50000);
	glTranslatef(-25000, -25000, -25000);

	glTranslatef(5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 0, 0, 1);
	glColor3f(255, 255, 255);
	glutSolidCone(.3f, .7f, 10, 10); // X axis.
	glRotatef(90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-5, 0, 0);

	for (float i = 0; i < 500; i++)
	{
		glTranslatef(i, 0, 0);
		glColor3f(255, 255, 255);
		glutSolidCube(.2f);
		glTranslatef(-i, 0, 0);

		glTranslatef(0, i, 0);
		glColor3f(255, 255, 255);
		glutSolidCube(.2f);
		glTranslatef(0, -i, 0);

		glTranslatef(0, 0, i);
		glColor3f(255, 255, 255);
		glutSolidCube(.2f);
		glTranslatef(0, 0, -i);
	}

	glTranslatef(-37, 0, -25);
	glutSolidSphere(3, 10, 10);
	glTranslatef(37, -0, 25);

	glTranslatef(37, 0, -25);
	glutSolidSphere(3, 10, 10);
	glTranslatef(-37, -0, 25);
}
