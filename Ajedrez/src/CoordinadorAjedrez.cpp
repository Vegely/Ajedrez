#include "CoordinadorAjedrez.h"
#include "ETSIDI.h"
#include "GestionMenus.h"
#include "CajaTexto.h"
#include "Partida.h"
#include <thread>
#include "Sonidos.h"

void hiloServidor(Servidor* servidor, std::string* mov_cliente) {
	servidor->conectarServidor();
	servidor->recibirDeCliente(*mov_cliente);
	std::cout << *mov_cliente;
}

void hiloCliente(Cliente* cliente) {
	cliente->conectarCliente();
	cliente->enviarAServidor("hola");
}

CoordinadorAjedrez::CoordinadorAjedrez() {
	estado = INICIO;
	Sonidos::con_comerAlPaso();
}

void CoordinadorAjedrez::dibuja() {
	if (estado == INICIO) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuInicial();
	}
	else if (estado == JUEGO) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
	//	mundo.dibuja();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy("juego", -5, 8);
	}
	else if (estado == INIT) {

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
		ETSIDI::setFont("Bitwise.ttf", 16);
		ranking.print();
		//ETSIDI::printxy(ranking.print(5).c_str(), -5, 8);
	}
	else if (estado == NUEVA_PARTIDA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuNuevaPartida();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(datosPartida.getNombre().c_str(), -5, 8);
	}
	else if (estado == CARGAR_PARTIDA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuCargarPartida();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(datosPartida.getNombre().c_str(), -5, 8);
	}
	else if (estado == J1) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuJugador(1);
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(datosPartida.getJ1().c_str(), -5, 8);
	}
	else if (estado == J2) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuJugador(2);
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
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
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy("ya existe", -5, 8);
	}
	else if (estado == PARTIDA_NO_EXISTE) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeMenuNoExiste();
	}
	else if (estado == CREAR_SALA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		//GestionMenus::imprimePartidaNaExiste();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(servidor->getip().c_str(), -5, 8);
	}
	else if (estado == UNIRSE_SALA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		//GestionMenus::imprimePartidaNaExiste();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(cliente->getIp().c_str(), -5, 8);
	}
}

void CoordinadorAjedrez::tecla(unsigned char key) {
	if (estado == INICIO) {
		if (key == 'w') {
			estado = CREAR_SALA;
			servidor->inicializa();
			hilo_servidor = new std::thread(hiloServidor, servidor, &mov_cliente);
		}
		if (key == 'u') {
			estado = UNIRSE_SALA;
			cliente->inicializa();
			hilo_cliente = new std::thread(hiloCliente, cliente);
		}
	}
	else if (estado == NUEVA_PARTIDA) {
		if((int)key != 9)
			datosPartida.getNombre() += key;
		if ((int)key == 9) {
			Sonidos::son_seleccionMenu();
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
			{
				Sonidos::son_seleccionMenu();
				estado = PARTIDA_EXISTE;
			}
			else {
				Sonidos::son_seleccionMenu();
				estado = JUEGO;
				datosPartida.crearPartida();
				ranking.aniadirJugador(datosPartida.getJ1(), 0);
			}
		}
		if ((int)key == 9 && datosPartida.getModo() == "Multijugador") {
			Sonidos::son_seleccionMenu();
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
			{
				Sonidos::son_seleccionMenu();
				estado = PARTIDA_EXISTE;
			}
			else {
				Sonidos::son_seleccionMenu();
				estado = JUEGO;
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
		{
			Sonidos::son_seleccionMenu();
			estado = PAUSA;
		}
		if ((int)key == 9)
			cliente->enviarAServidor(mov_cliente);
		if (key == 's')
			exit(0);
	}
	else if (estado == CARGAR_PARTIDA) {
		if ((int)key != 9) //9 = tabulador
			datosPartida.getNombre() += key;
		if ((int)key == 9) {
			datosPartida.getNombre() += ".txt";
			if (datosPartida.existe()) {
				Sonidos::son_seleccionMenu();
				datosPartida.cargarPartida();
				estado = JUEGO;
			}
			else {
				Sonidos::son_seleccionMenu();
				estado = PARTIDA_NO_EXISTE;
			}

		}
		if ((int)key == 127) { //127 = suprimir
			datosPartida.getNombre() = "";
		}
	}
	else if (estado == PARTIDA_EXISTE) {
		if (key == 'c') {
			Sonidos::son_seleccionMenu();
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
			cliente->conectarCliente();
			cliente->enviarAServidor("luismi es muy gay");
			Sonidos::son_seleccionMenu();
			estado = JUEGO;
		}
		if (key == 'v') {
			cliente->desconectarCliente();
			hilo_cliente->join();
		}
	}
	else if (estado == CREAR_SALA) {
		if (key == 'v') {
			Sonidos::son_seleccionMenu();
			estado = PAUSA;
			servidor->enviarACliente("desconecta");
			servidor->desconectarServidor();
			hilo_servidor->join();
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
		static CajaTexto c_salir({ -1,-2.25 }, { -4,-2.25 }, { -4,-3.25 }, { -1,-3.25 });
		static CajaTexto c_ranking({ 0, 0.75 }, { -4, 0.75 }, { -4,  -0.25 }, { 0,-0.25 });
		static CajaTexto c_cargar_partida({ 4, 6.75 }, { -4, 6.75 }, { -4,  5.75 }, { 4,5.75 });
		static CajaTexto c_nueva_partida({ 3.5, 9.75 }, { -4, 9.75 }, { -4,  8.75 }, { 3.5,8.75 });
		static CajaTexto c_salas({ 3, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 3, 2.75 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_salir.click(x, y))
			{
				Sonidos::son_seleccionMenu();
				exit(0);
			}
			if (c_ranking.click(x, y))
			{
				Sonidos::son_seleccionMenu();
				estado = RANKING;
			}
			if (c_cargar_partida.click(x, y))
			{
				Sonidos::son_seleccionMenu();
				estado = CARGAR_PARTIDA;
			}
			if (c_nueva_partida.click(x, y))
			{
				Sonidos::son_seleccionMenu();
				estado = NUEVA_PARTIDA;
			}
			if (c_salas.click(x, y))
			{
				Sonidos::son_seleccionMenu();
				estado = CREAR_SALA;
			}
		}
	}
	else if (estado == NUEVA_PARTIDA) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_volver.click(x, y)) {
				Sonidos::son_seleccionMenu();
				datosPartida.getNombre() = "";
				estado = INICIO;
			}
		}
	}
	else if (estado == MODO) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		static CajaTexto c_inteligencia({ 2.5, 8.75 }, { -9, 8.75 }, { -9,  7.75 }, { 2.5, 7.75 });
		static CajaTexto c_normal({ -5.5, 4.75 }, { -9, 4.75 }, { -9,  3.75 }, { -5.5, 3.75 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_volver.click(x, y))
			{
				Sonidos::son_seleccionMenu();
				datosPartida.getNombre() = "";
				estado = NUEVA_PARTIDA;
			}
			else if (c_inteligencia.click(x, y))
			{
				Sonidos::son_seleccionMenu();
				datosPartida.getModo() += "Individual";
				estado = J1;
			}

			else if (c_normal.click(x, y))
			{
				Sonidos::son_seleccionMenu();
				datosPartida.getModo() += "Multijugador";
				estado = J1;
			}
		}
	}
	else if (estado == J1) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_volver.click(x, y)) {
				Sonidos::son_seleccionMenu();
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
				Sonidos::son_seleccionMenu();
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
				Sonidos::son_seleccionMenu();
				datosPartida.getNombre() = "";
				estado = INICIO;
			}
		}
	}
	else if (estado == PARTIDA_NO_EXISTE) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_volver.click(x, y)) {
				Sonidos::son_seleccionMenu();
				estado = INICIO;
				datosPartida.getNombre() = "";
			}
		}
	}
	else if (estado == RANKING) {
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (c_volver.click(x, y)) {
				Sonidos::son_seleccionMenu();
				estado = INICIO;
			}
		}
	}
}




