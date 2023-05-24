#include "GestionMenus.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include "Caja.h"
#include <string>
#include "CajaTexto.h"


void GestionMenus::imprimeMenuInicial() {

	

	//static CajaTexto c({ 10,5 }, { -10,5 }, { -10,0 }, { 10,0 },"PUTA MADRE");
	//static CajaTexto c({ 10,15 }, { -10,15 }, { -10,10 }, { 10,10 },"texto");
	static CajaTexto c_salir({ -1,-2.25 }, { -4,-2.25}, { -4,-3.25 }, { -1,-3.25}, "puta vida");
	//c_salir.dibuja();
	static CajaTexto c_ranking({ 0, 0.75 }, { -4, 0.75 }, { -4,  -0.25 }, { 0,-0.25 }, "tus muertos");
	//c_ranking.dibuja();
	static CajaTexto c_cargar_partida({ 4, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 4,2.75 }, "tus muertos");
	//c_cargar_partida.dibuja();
	static CajaTexto c_nueva_partida({3.5, 6.75}, {-4, 6.75}, {-4,  5.75}, {3.5,5.75}, "tus muertos");
	//c_nueva_partida.dibuja();
	
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
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont("ALGER.ttf", 60);
	ETSIDI::printxy("AJEDREZ", -6, 12);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont("ALGER.ttf", 20);
	ETSIDI::printxy("Nueva Partida", -4, 6);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont("ALGER.ttf", 20);
	ETSIDI::printxy("Cargar Partida", -4, 3);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont("ALGER.ttf", 20);
	ETSIDI::printxy("Ranking", -4, 0);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont("ALGER.ttf", 20);
	ETSIDI::printxy("Salir", -4, -3);
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
	static CajaTexto c_reanudar({ 1, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 1, 2.75}, "tus muertos");
	c_reanudar.dibuja();
	static CajaTexto c_salir({-1, 0.75}, {-4, 0.75}, {-4,  -0.25}, {-1, -0.25}, "tus muertos");
	c_salir.dibuja();
	ETSIDI::setTextColor(1, 0, 0);
	ETSIDI::setFont("ALGER.ttf", 60);
	ETSIDI::printxy("PAUSA", -6, 12);
	ETSIDI::setTextColor(0, 1, 0);
	ETSIDI::setFont("ALGER.ttf", 20);
	ETSIDI::printxy("Reanudar", -4, 3);
	ETSIDI::setTextColor(0, 1, 0);
	ETSIDI::setFont("ALGER.ttf", 20);
	ETSIDI::printxy("Salir", -4, 0);
}

