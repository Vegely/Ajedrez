#include "CoordinadorAjedrez.h"
#include "ETSIDI.h"
#include "GestionMenus.h"
#include "Partida.h"
#include <thread>

void foo(Servidor* servidor, std::string* mov_cliente) {
	servidor->conectarServidor();
	servidor->recibirDeCliente(*mov_cliente);
	std::cout << *mov_cliente;
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
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
	//	mundo.dibuja();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy("juego", -5, 8);
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
		//GestionMenus::imprimeRanking();

		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ranking.print();
		//ETSIDI::printxy(ranking.print(5).c_str(), -5, 8);
	}
	else if (estado == NUEVA_PARTIDA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeNuevaPartida();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(datosPartida.getNombre().c_str(), -5, 8);
	}
	else if (estado == CARGAR_PARTIDA) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeCargarPartida();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(datosPartida.getNombre().c_str(), -5, 8);
	}
	else if (estado == J1) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeJ1();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(datosPartida.getJ1().c_str(), -5, 8);
	}
	else if (estado == J2) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeJ2();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy(datosPartida.getJ2().c_str(), -5, 8);
	}
	else if (estado == MODO) {
		gluLookAt(0, 7.5, 30, // posicion del ojo
			0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
			0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 
		GestionMenus::imprimeModo();
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
		//GestionMenus::imprimePartidaNaExiste();
		ETSIDI::setTextColor(1, 1, 0);
		ETSIDI::setFont("Bitwise.ttf", 16);
		ETSIDI::printxy("no existe", -5, 8);
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
		ETSIDI::printxy(cliente.getIp().c_str(), -5, 8);
	}
}

void CoordinadorAjedrez::tecla(unsigned char key) {
	if (estado == INICIO) {
		if (key == 'n')
			estado = NUEVA_PARTIDA;
		if (key == 'c')
			estado = CARGAR_PARTIDA;
		if (key == 'r')
			estado = RANKING;
		if (key == 'w') {
			estado = CREAR_SALA;
			servidor->inicializa();
			//servidor->conectarServidor();
			hilo_servidor = new std::thread(foo, servidor, &mov_cliente);
		}
		if (key == 'u') {
			estado = UNIRSE_SALA;
			cliente.inicializa();
		}
		if (key == 's')
			exit(0);
	}
	else if (estado == RANKING) {
		if (key == 'v')
			estado = INICIO;
	}
	else if (estado == NUEVA_PARTIDA) {
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
	else if (estado == MODO) {
		if (key == 'i') {
			datosPartida.getModo() += "Individual";
			estado = J1;
		}
		if (key == 'd') {
			datosPartida.getModo() += "Multijugador";
			estado = J1;
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
				estado = JUEGO;
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
			estado = PAUSA;
		if ((int)key == 9)
			cliente.enviarAServidor(mov_cliente);
		if (key == 's')
			exit(0);
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
	else if (estado == PARTIDA_NO_EXISTE) {
		if (key == 'i'){
			estado=INICIO;
			datosPartida.getNombre() = "";
		}
	}
	else if (estado == UNIRSE_SALA) {
		if ((int)key != 9)
			cliente.getIp() += key;
		if ((int)key == 9) {
			cliente.conectarCliente();
			estado = JUEGO;
		}
	}
	else if (estado == CREAR_SALA) {
		if (key == 'v') {
			estado = PAUSA;
			//hilo_servidor->join();
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
			if (cliente.getIp().length() > 0)
				cliente.getIp() = cliente.getIp().substr(0, cliente.getIp().length() - 1);
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

/*void CoordinadorAjedrez::click(int button, int state, int x, int y) {

}*/



