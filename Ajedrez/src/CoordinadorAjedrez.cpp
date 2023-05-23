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

void CoordinadorAjedrez::click(int button, int state, int x, int y) {
	if (estado == INICIO) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
			//if (x >= (11.7/43.4)*glutGet(GLUT_WINDOW_WIDTH) && x<=(31.7/43.4)*glutGet(GLUT_WINDOW_WIDTH)
			//	&& y>=(20.0/35.0)*glutGet(GLUT_WINDOW_HEIGHT) && y <= (25.0 / 35.0) * glutGet(GLUT_WINDOW_HEIGHT))
				estado = JUEGO;

		std::cout << x <<  std::endl;
	}
	if (estado == JUEGO) {
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
			estado = INICIO;
	}
}