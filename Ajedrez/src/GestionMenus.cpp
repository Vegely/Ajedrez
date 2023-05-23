#include "GestionMenus.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include "Caja.h"
#include <string>
#include "CajaTexto.h"


void GestionMenus::imprimeMenuInicial() {
	static CajaTexto c2({ 10,5 }, { -10,5 }, { -10,0 }, { 10,0 }, "puta vida");
	c2.dibuja();
}

void GestionMenus::imprimeMenuPausa() {
	float fscala = 100;
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 

	glColor3ub(255, 0, 0);
	glTranslatef(-5,10, 0);
	glScaled(1 / fscala, 1 / fscala, 1 / fscala);
	for (char c : "PAUSA")
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);

}
void GestionMenus::imprimeNuevaPartida() {
	static CajaTexto c2({ 5,5 }, { -5,5 }, { -5,0 }, { 5,0 }, "puta vida");
	c2.dibuja();
}
void GestionMenus::imprimeRanking() {

}
void GestionMenus::imprimeCargarPartida() {

}
void GestionMenus::imprimeJ1() {

}
void GestionMenus::imprimeJ2() {

}
void GestionMenus::imprimeModo() {

}

