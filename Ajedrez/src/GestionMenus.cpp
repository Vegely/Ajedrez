#include "GestionMenus.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include "Caja.h"
#include <string>
#include "CajaTexto.h"


void GestionMenus::imprimeMenuInicial() {

	//static CajaTexto c({ 10,5 }, { -10,5 }, { -10,0 }, { 10,0 },"PUTA MADRE");
	//static CajaTexto c({ 10,15 }, { -10,15 }, { -10,10 }, { 10,10 },"texto");
	static CajaTexto c_salir({ 8,-2 }, { -8,-2}, { -8,-4 }, { 8,-4 }, "puta vida");
	c_salir.dibuja();
	static CajaTexto c_ranking({ 8, 1 }, { -8, 1 }, { -8,  -1 }, { 8,-1 }, "tus muertos");
	c_ranking.dibuja();
	static CajaTexto c_cargar_partida({ 8, 4 }, { -8, 4 }, { -8,  2 }, { 8,2 }, "tus muertos");
	c_cargar_partida.dibuja();
	static CajaTexto c_nueva_partida({8, 7}, {-8, 7}, {-8,  5}, {8,5}, "tus muertos");
	c_nueva_partida.dibuja();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("prueba.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2f(-21, -8);
	glTexCoord2d(1, 1); glVertex2f(21, -8);
	glTexCoord2d(1, 0); glVertex2f(21, 24);
	glTexCoord2d(0, 0); glVertex2f(-21, 24);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	//c.dibuja();
	


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
	static CajaTexto c_reanudar({ 8, 1 }, { -8, 1 }, { -8,  -1 }, { 8,-1 }, "tus muertos");
	c_reanudar.dibuja();
	static CajaTexto c_salir({ 8, 4 }, { -8, 4 }, { -8,  2 }, { 8,2 }, "tus muertos");
	c_salir.dibuja();
	glColor3ub(255, 0, 0);
	glTranslatef(-4, 15, 0);
	glScaled(1 / fscala, 1 / fscala, 1 / fscala);
	for (char c : "PAUSA")
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
	glTranslatef(0, 0, 0);
}

