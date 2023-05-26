#include "CoordinadorAjedrez.h"
#include "ETSIDI.h"
#include "GestionMenus.h"
#include "CajaTexto.h"
#include "Partida.h"
#include <thread>

#define DIR_FUENTE "fuentes/Bitwise.ttf"

ConfiguracionDeJuego configuracion;

void hiloServidor(Servidor* servidor, std::string* mov_cliente, Estado* estado, bool* salir, std::string* m_cliente, bool* reset) {
	servidor->conectarServidor();
	*estado = J1;

	while (!(*salir)) {
		//if (m_cliente->c_str() == "") {
			servidor->recibirDeCliente(*m_cliente);
			std::cout << *m_cliente;
		//}
		/*if (*reset) {
			*m_cliente = "";
		}*/
	}
}

void hiloCliente(Cliente* cliente, Estado* estado, bool* salir, std::string* m_servidor, bool* reset) {
	if (!cliente->conectarCliente()) {
		*estado = NO_CONECTADO;
	}
	else
		*estado = JUEGO;
	while (!(*salir)) {
		//if (m_servidor->c_str() == "") {
			cliente->recibirDeServidor(*m_servidor);
			std::cout << *m_servidor;
		//}
		//if (*reset) {
		//	*m_servidor = "";
		//}
	}
}

CoordinadorAjedrez::CoordinadorAjedrez() {
	estado = INICIO;
}

void CoordinadorAjedrez::dibuja() {
	if (estado == INICIO) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuInicial();
	}
	else if (estado == JUEGO) {
	/*	static MotorDeJuego juego(configuracion);

		if (inicializarPartida)
		{
			juego = MotorDeJuego(configuracion);

			for (ConfiguracionDeJuego::FormasDeInteraccion configJugador : configuracion.config)
				if (configJugador == ConfiguracionDeJuego::FormasDeInteraccion::IA) srand(time(NULL)); // Inicializar la semilla si hay IA

			inicializarPartida = false;
		}*/

		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)
		
		//DatosFinal datosFinal = juego.motor();

		//if (datosFinal.exit)
		//	juego.liberar();// estado = GAMEOVER;
			

		//mundo.dibuja();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy("juego", -5, 8);
	}
	else if (estado == COLORJ1) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuColorJ1();
	}
	else if (estado == INIT) {
		inicializarPartida = true;
		estado = JUEGO;
	}
	else if (estado == PAUSA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuPausa();
	}
	else if (estado == RANKING) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuRanking();

		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ranking.print();
		//ETSIDI::printxy(ranking.print(5).c_str(), -5, 8);
	}
	else if (estado == NUEVA_PARTIDA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuNuevaPartida();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy(datosPartida.getNombre().c_str(), -5, 8);
	}
	else if (estado == CARGAR_PARTIDA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuCargarPartida();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy(datosPartida.getNombre().c_str(), -5, 8);
	}
	else if (estado == J1) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuJugador(1);
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy(datosPartida.getJ1().c_str(), -5, 8);
	}
	else if (estado == J2) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuJugador(2);
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy(datosPartida.getJ2().c_str(), -5, 8);
	}
	else if (estado == MODO) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuModo();
	}
	else if (estado == PARTIDA_EXISTE) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		//GestionMenus::imprimePartidaYaExiste();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy("ya existe", -5, 8);
	}
	else if (estado == PARTIDA_NO_EXISTE) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		//GestionMenus::imprimePartidaNaExiste();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy("no existe", -5, 8);
	}
	else if (estado == CREAR_SALA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuCrearSala();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy(servidor->getip().c_str(), -5, 8);
	}
	else if (estado == UNIRSE_SALA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuUnirseSala();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont(DIR_FUENTE, 16);
		ETSIDI::printxy(cliente->getIp().c_str(), -5, 8);
	}
	else if (estado == NO_CONECTADO) {
			estado = MODO;
			datosPartida.getModo() = "";
			cliente->desconectarCliente();
			hilo_cliente->join();
	}
}

void CoordinadorAjedrez::tecla(unsigned char key) {
	if (estado == NUEVA_PARTIDA) {
		if((int)key != 9)
			datosPartida.getNombre() += key;
		if ((int)key == 9) {
			estado = MODO;
			datosPartida.getNombre() += ".txt";
		}
		if ((int)key == 127) {
			datosPartida.getNombre() = "";
		}
	}
	else if (estado == J1) {
		if ((int)key != 9)
			datosPartida.getJ1() += key;
		if ((int)key == 9 && datosPartida.getModo() == "Individual") { //Se carga la partida
			if (datosPartida.getJ1() == "")
				datosPartida.getJ1() = "J1"; //En el caso de que el jugador no introduzca un nombre se pone uno por defecto
			if (datosPartida.existe())
				estado = PARTIDA_EXISTE; 
			else {
				estado = COLORJ1;
				datosPartida.crearPartida();
				ranking.aniadirJugador(datosPartida.getJ1(), 0);
			}
		}
		if ((int)key == 9 && datosPartida.getModo() == "Multijugador") {
			estado = J2;
			if (datosPartida.getJ1() == "")
				datosPartida.getJ1() = "J1";
			ranking.aniadirJugador(datosPartida.getJ1(), 0);
		}
		if ((int)key == 127) {
			datosPartida.getJ1() = "";
		}
	}
	else if (estado == J2) {
		if ((int)key != 9)
			datosPartida.getJ2() += key;
		if ((int)key == 9) {
			if (datosPartida.getJ2() == "")
				datosPartida.getJ2() = "J2";
			if (datosPartida.existe())
				estado = PARTIDA_EXISTE;
			else {
				estado = COLORJ1;
				datosPartida.crearPartida();
				ranking.aniadirJugador(datosPartida.getJ2(), 0);
			}
		}
		if ((int)key == 127) {//127 = suprimir
			datosPartida.getJ2() = "";
		}
	}
	else if (estado == JUEGO) {
		if (key == 'p')
			estado = PAUSA;
		if (key == 'a' /* && datosPartida.getModo() == "Red"*/) {
			cliente->enviarAServidor("hola");
		}
		if (key == 'b' && datosPartida.getModo() == "Red") {
			servidor->enviarACliente("mundo");
		}
		if (key == 'r')
			reset = 1;
	}
	else if (estado == CARGAR_PARTIDA) {
		if ((int)key != 9) //9 = tabulador
			datosPartida.getNombre() += key;
		if ((int)key == 9) {
			datosPartida.getNombre() += ".txt";
			if (datosPartida.existe()) {
				datosPartida.cargarPartida();
				estado = JUEGO;
			}
			else {
				estado = PARTIDA_NO_EXISTE;
			}

		}
		if ((int)key == 127) { //127 = suprimir
			datosPartida.getNombre() = "";
		}
	}
	else if (estado == PARTIDA_EXISTE) {
		if (key == 'c') {
			estado = JUEGO;
			datosPartida.cargarPartida();
		}
		else if (key == 'i') {
			estado = INICIO;
			datosPartida.getNombre() = "";
			datosPartida.getJ1() = "";
			datosPartida.getJ2() = "";
			datosPartida.getModo() = "";
		}
	}
	else if (estado == UNIRSE_SALA) {
		if ((int)key != 9)
			cliente->getIp() += key;
		if ((int)key == 9) {
			cliente->inicializa();
			hilo_cliente = new std::thread(hiloCliente, cliente, &estado, &salir, &mov_cliente, &reset);
		}
	}
}

void CoordinadorAjedrez::teclaEspecial(int key) {
	if (estado == CARGAR_PARTIDA) {
		if (key == GLUT_KEY_LEFT) {
			if (datosPartida.getNombre().length() > 0)
				datosPartida.getNombre() = datosPartida.getNombre().substr(0, datosPartida.getNombre().length() - 1);
		}
	}
	else if (estado == J1) {
		if (key == GLUT_KEY_LEFT) {
			if (datosPartida.getJ1().length() > 0)
				datosPartida.getJ1() = datosPartida.getJ1().substr(0, datosPartida.getJ1().length() - 1);
		}
	}
	else if (estado == J2) {
		if (key == GLUT_KEY_LEFT) {
			if (datosPartida.getJ2().length() > 0)
				datosPartida.getJ2() = datosPartida.getJ2().substr(0, datosPartida.getJ2().length() - 1);
		}
	}
	else if (estado == NUEVA_PARTIDA) {
		if (key == GLUT_KEY_LEFT) {
			if (datosPartida.getNombre().length() > 0)
				datosPartida.getNombre() = datosPartida.getNombre().substr(0, datosPartida.getNombre().length() - 1);
		}
	}
	else if (estado == UNIRSE_SALA) {
		if (key == GLUT_KEY_LEFT) {
			if (cliente->getIp().length() > 0)
				cliente->getIp() = cliente->getIp().substr(0, cliente->getIp().length() - 1);
		}
	}
	else if (estado == RANKING) {
		if (key == GLUT_KEY_RIGHT)
			ranking.paginaSiguiente();
		if (key == GLUT_KEY_LEFT) {
			ranking.paginaAnterior();
		}
	}
}

void CoordinadorAjedrez::click(int button, int state, int x, int y) {
	if (estado == INICIO) {
		static CajaTexto c_salir({ 0, 0.75 }, { -4, 0.75 }, { -4,  -0.25 }, { 0,-0.25 });
		static CajaTexto c_ranking({ 3, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 3, 2.75 }); 
		static CajaTexto c_cargar_partida({ 4, 6.75 }, { -4, 6.75 }, { -4,  5.75 }, { 4,5.75 });
		static CajaTexto c_nueva_partida({ 3.5, 9.75 }, { -4, 9.75 }, { -4,  8.75 }, { 3.5,8.75 });
		//static CajaTexto c_salas({ 3, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 3, 2.75 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_salir.click(x, y))
				exit(0);
			if (c_ranking.click(x, y))
				estado = RANKING;
			if (c_cargar_partida.click(x, y))
				estado = CARGAR_PARTIDA;
			if (c_nueva_partida.click(x, y))
				estado = NUEVA_PARTIDA;
			/*if (c_salas.click(x, y))
				estado = CREAR_SALA;*/
		}
	}
	else if (estado == NUEVA_PARTIDA) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_volver.click(x, y)) {
				datosPartida.getNombre() = "";
				estado = INICIO;
			}
		}
	}
	else if (estado == MODO) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		static CajaTexto c_inteligencia({ 10, 6.75 }, { -4, 6.75 }, { -4,  5.75 }, { 10,5.75 });
		static CajaTexto c_normal({ 0.5, 9.75 }, { -4, 9.75 }, { -4,  8.75 }, { 0.5,8.75 });
		static CajaTexto c_crear_sala({ 3, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 3, 2.75 });
		static CajaTexto c_unirse_sala({ 7, 0.75 }, { -4, 0.75 }, { -4,  -0.25 }, { 7,-0.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_volver.click(x, y))
			{
				datosPartida.getNombre() = "";
				estado = NUEVA_PARTIDA;
			}
			else if (c_inteligencia.click(x, y))
			{
				configuracion = { ConfiguracionDeJuego::FormasDeInteraccion::LOCAL, ConfiguracionDeJuego::FormasDeInteraccion::IA };
				datosPartida.getModo() += "Individual";
				estado = J1;
			}
			else if (c_normal.click(x, y))
			{
				configuracion = { ConfiguracionDeJuego::FormasDeInteraccion::LOCAL, ConfiguracionDeJuego::FormasDeInteraccion::LOCAL };
				datosPartida.getModo() += "Multijugador";
				estado = J1;
			}
			else if (c_crear_sala.click(x, y)) {
				datosPartida.getModo() = "Red";
				estado = CREAR_SALA;
				servidor->inicializa();
				hilo_servidor = new std::thread(hiloServidor, servidor, &mov_cliente, &estado, &salir, &mov_servidor, &reset);
			}
			else if (c_unirse_sala.click(x, y)) {
				datosPartida.getModo() = "Red";
				estado = UNIRSE_SALA;
			}
		}
	}
	else if (estado == J1) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_volver.click(x, y)) {
				datosPartida.getModo() = "";
				estado = MODO;
			}
		}
	}
	else if(estado == J2) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_volver.click(x, y)) {
				datosPartida.getJ1() = "";
				estado = J1;
			}
		}
	}
	else if (estado == CARGAR_PARTIDA) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_volver.click(x, y)) {
				datosPartida.getNombre() = "";
				estado = INICIO;
			}
		}
	}
	else if (estado == PARTIDA_NO_EXISTE) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_volver.click(x, y)) {
				estado = INICIO;
				datosPartida.getNombre() = "";
			}
		}
	}
	else if (estado == RANKING) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_volver.click(x, y)) {
				estado = INICIO;
			}
		}
	}
	else if (estado == CREAR_SALA) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_volver.click(x,y)) {
				estado = MODO;
				datosPartida.getModo() = "";
				servidor->desconectarServidor();
				hilo_servidor->join();
			}
		}
	}
	else if (estado == UNIRSE_SALA) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_volver.click(x, y)) {
				estado = MODO;
				datosPartida.getModo() = "";
			}
		}
	}
	else if (estado == COLORJ1) {
		static std::string aux = "";
		static CajaTexto c_blanco({ 0.5, 9.75 }, { -4, 9.75 }, { -4,  8.75 }, { 0.5,8.75 });
		static CajaTexto c_negro({ 10, 6.75 }, { -4, 6.75 }, { -4,  5.75 }, { 10,5.75 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_blanco.click(x, y)) {
				estado = INIT;
			}
			if (c_negro.click(x, y)) {
				estado = INIT;
				aux = datosPartida.getJ1();
				datosPartida.getJ1() = datosPartida.getJ2();
				datosPartida.getJ1() = aux;

				if(datosPartida.getModo()=="Individual")
					configuracion = { ConfiguracionDeJuego::FormasDeInteraccion::IA, ConfiguracionDeJuego::FormasDeInteraccion::LOCAL };
			}
		}
	}
	else if (estado == PAUSA) {
		static CajaTexto c_reanudar({ 2, 9.75 }, { -4, 9.75 }, { -4,  8.75 }, { 2, 8.75 });
		static CajaTexto c_salir({ 12, 3.75 }, { -8, 3.75 }, { -8,  2.75 }, { 12, 2.75 });
		static CajaTexto c_guardar({ 13, 6.75 }, { -8, 6.75 }, { -8,  5.75 }, { 13, 5.75 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_reanudar.click(x, y)) {
				estado = JUEGO;
			}
			if (c_salir.click(x, y)) {
				if (cliente != nullptr && datosPartida.getModo() == "Red") {
					cliente->desconectarCliente();
					hilo_cliente->join();
				}
				else if (servidor != nullptr && datosPartida.getModo() == "Red") {
					servidor->desconectarServidor();
					hilo_servidor->join();
				}
				estado = INICIO;
				remove(datosPartida.getNombre().c_str());
				datosPartida.getJ1() = "";
				datosPartida.getJ2() = "";
				datosPartida.getModo() = "";
				datosPartida.getNombre() = "";
			}
			else if (c_guardar.click(x, y)) {
				estado = INICIO;
				datosPartida.guardarPartida();
				datosPartida.getJ1() = "";
				datosPartida.getJ2() = "";
				datosPartida.getModo() = "";
				datosPartida.getNombre() = "";
			}
		}
	}
}




