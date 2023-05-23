#include "GestionMenus.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include "Caja.h"
#include <string>
#include "CajaTexto.h"


void GestionMenus::imprimeMenuInicial() {

	//static CajaTexto c({ 10,5 }, { -10,5 }, { -10,0 }, { 10,0 },"PUTA MADRE");
	//static CajaTexto c({ 10,15 }, { -10,15 }, { -10,10 }, { 10,10 },"texto");
	static CajaTexto c2({ 10,5 }, { -10,5}, { -10,0 }, { 10,0 }, "puta vida");
	
	//c.dibuja();
	c2.dibuja();


	//c2.dibuja();
/*	glDisable(GL_LIGHTING);
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(10, 15, 0);
	glVertex3d(-10, 15, 0);
	glVertex3d(-10, 10, 0);
	glVertex3d(10, 10, 0);
	glEnd();
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHTING);
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3d(10, 15, 0);
	glVertex3d(-10, 15, 0);
	glVertex3d(-10, 10, 0);
	glVertex3d(10, 10, 0);
	glEnd();
	glEnable(GL_LIGHTING);*/
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

