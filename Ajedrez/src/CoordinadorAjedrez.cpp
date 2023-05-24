#include "CoordinadorAjedrez.h"
#include "ETSIDI.h"
#include "GestionMenus.h"
#include "CajaTexto.h"

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
	else if (estado == CARGAR)
	{
		GestionMenus::imprimeMenuCargarPartida();
	}
	else if (estado == NUEVA)
	{
		GestionMenus::imprimeMenuNuevaPartida();
	}
	else if (RANKING)
	{
		GestionMenus::imprimeMenuRanking();
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


void CoordinadorAjedrez::click(int button, int state, int x, int y) {
	if (estado == INICIO) {
		static CajaTexto c_salir({ -1,-2.25 }, { -4,-2.25 }, { -4,-3.25 }, { -1,-3.25 }, "puta vida");
		static CajaTexto c_ranking({ 0, 0.75 }, { -4, 0.75 }, { -4,  -0.25 }, { 0,-0.25 }, "tus muertos");
		static CajaTexto c_cargar_partida({ 4, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 4,2.75 }, "tus muertos");
		static CajaTexto c_nueva_partida({ 3.5, 6.75 }, { -4, 6.75 }, { -4,  5.75 }, { 3.5,5.75 }, "tus muertos");
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_salir.click(x, y))
			{
				estado = FIN;
			}
			if (c_ranking.click(x, y))
			{
				estado = RANKING;
			}
			if (c_cargar_partida.click(x, y))
			{
				estado = CARGAR;
				std::cout << estado << std::endl;

			}
			if (c_nueva_partida.click(x, y))
				estado = NUEVA;
		}

	}
	else if (estado == PAUSA) {
		static CajaTexto c_reanudar({ 1, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 1, 2.75 }, "tus muertos");
		static CajaTexto c_salir({ -1, 0.75 }, { -4, 0.75 }, { -4,  -0.25 }, { -1, -0.25 }, "tus muertos");
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if (c_reanudar.click(x, y))
				estado = JUEGO;
			if (c_salir.click(x, y))
				estado = INICIO;
		}
	}
	else if (estado == JUEGO)
	{
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
			estado = PAUSA;
	}
	else if (estado == CARGAR)
	{
		static CajaTexto c_nombrepartida({ 1, 3.75 }, { -6, 3.75 }, { -6,  2.75 }, { 1, 2.75 }, "tus muertos");
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 }, "tus muertos");
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			if (c_nombrepartida.click(x, y))
				estado = EXISTE;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			if (c_volver.click(x, y))
				estado = INICIO;
	}
	else if (estado == NUEVA)
	{
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 }, "tus muertos");
		static CajaTexto c_nombrepartida({ 1, 3.75 }, { -6, 3.75 }, { -6,  2.75 }, { 1, 2.75 }, "tus muertos");
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			if (c_nombrepartida.click(x, y))
				estado = JUEGO;
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			if (c_volver.click(x, y))
				estado = INICIO;
	}
	else if (estado == RANKING)
	{
		static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 }, "tus muertos");
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			if (c_volver.click(x, y))
				estado = INICIO;
	}
}