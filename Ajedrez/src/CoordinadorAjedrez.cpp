#include "CoordinadorAjedrez.h"
#include "ETSIDI.h"
#include "GestionMenus.h"

/*
	Silenciado:
	- main: test unitario
	- callback.cpp: ondraw
*/


CoordinadorAjedrez::CoordinadorAjedrez() {
	estado = INICIO;
}

void CoordinadorAjedrez::dibuja() {
	if (estado == INICIO) {
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