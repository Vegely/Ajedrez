#include "CoordinadorAjedrez.h"
#include "ETSIDI.h"
#include "GestionMenus.h"


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
		mundo.dibuja();
	}
	else if (estado == FIN) {
		float y;
	}
	else if (estado == PAUSA) {
		GestionMenus::imprimeMenuPausa();
	}
}

void CoordinadorAjedrez::tecla(unsigned char key) {
	if (estado == INICIO) {
		if(key == 'j')
			estado = JUEGO;
		if (key == 's')
			exit(0);
	}
	else if (estado == JUEGO) {
		if (key == 'p')
			estado = PAUSA;
	}
	else if (estado == PAUSA) {
		if (key == 'c')
			estado = JUEGO;
	}
}
#include "CajaTexto.h"

void CoordinadorAjedrez::click(int button, int state, int x, int y) {
	if (estado == INICIO) {
		static CajaTexto c_salir({ 8,-2 }, { -8,-2 }, { -8,-4 }, { 8,-4 }, "puta vida");
		static CajaTexto c_ranking({ 8, 1 }, { -8, 1 }, { -8,  -1 }, { 8,-1 }, "tus muertos");
		static CajaTexto c_cargar_partida({ 8, 4 }, { -8, 4 }, { -8,  2 }, { 8,2 }, "tus muertos");
		static CajaTexto c_nueva_partida({ 8, 7 }, { -8, 7 }, { -8,  5 }, { 8,5 }, "tus muertos");
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_salir.click(x, y))
				estado = FIN;
			if (c_ranking.click(x, y))
			estado = RANKING;
			if (c_cargar_partida.click(x, y))
			estado = CARGAR;
			if (c_nueva_partida.click(x, y))
				estado = NUEVA;
		}

	}
	if (estado == PAUSA) {
		static CajaTexto c_reanudar({ 8, 1 }, { -8, 1 }, { -8,  -1 }, { 8,-1 }, "tus muertos");
		static CajaTexto c_salir({ 8, 4 }, { -8, 4 }, { -8,  2 }, { 8,2 }, "tus muertos");
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			std::cout << x << std::endl;
			if (c_reanudar.click(x, y))
				estado = JUEGO;
			if (c_salir.click(x, y))
				estado = INICIO;
		}
	}
	if (estado == JUEGO)
	{
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
			estado = PAUSA;
	}
}