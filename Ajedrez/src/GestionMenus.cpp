#include "GestionMenus.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include "Caja.h"
#include <string>
#include "CajaTexto.h"
#include <iostream>

#define DIR_ALGER "fuentes/ALGER.ttf"

void GestionMenus::imprimeMenuInicial() {
	//static CajaTexto c({ 10,5 }, { -10,5 }, { -10,0 }, { 10,0 },"PUTA MADRE");
	//static CajaTexto c({ 10,15 }, { -10,15 }, { -10,10 }, { 10,10 },"texto");
	static CajaTexto c_salir({ -1,-2.25 }, { -4,-2.25}, { -4,-3.25 }, { -1,-3.25});
	//c_salir.dibuja();
	static CajaTexto c_ranking({ 0, 0.75 }, { -4, 0.75 }, { -4,  -0.25 }, { 0,-0.25 });
	//c_ranking.dibuja();
	static CajaTexto c_cargar_partida({ 4, 6.75 }, { -4, 6.75 }, { -4,  5.75 }, { 4,5.75 });
	//c_cargar_partida.dibuja();
	static CajaTexto c_nueva_partida({3.5, 9.75}, {-4, 9.75}, {-4,  8.75}, {3.5,8.75});
	//c_nueva_partida.dibuja();
	static CajaTexto c_salas({ 3, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 3, 2.75 });
	//c_salas.dibuja();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("AJEDREZ", -6, 12);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Nueva Partida", -4, 9);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Cargar Partida", -4, 6);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Salas", -4, 3);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Ranking", -4, 0);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Salir", -4, -3);
}

void GestionMenus::imprimeMenuPausa() {
	static CajaTexto c_reanudar({ 1, 3.75 }, { -4, 3.75 }, { -4,  2.75 }, { 1, 2.75});
	//c_reanudar.dibuja();
	static CajaTexto c_salir({-1, 0.75}, {-4, 0.75}, {-4,  -0.25}, {-1, -0.25});
	//c_salir.dibuja();
	ETSIDI::setTextColor(1, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("PAUSA", -6, 12);
	ETSIDI::setTextColor(0, 1, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Reanudar", -4, 3);
	ETSIDI::setTextColor(0, 1, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Salir", -4, 0);
}

void GestionMenus::imprimeMenuCargarPartida()
{
	static CajaTexto c_nombrepartida({ 1, 3.75 }, { -6, 3.75 }, { -6,  2.75 }, { 1, 2.75 });
	c_nombrepartida.dibuja();
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("CARGAR PARTIDA", -8, 12);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Nombre de la partida:", -6, 4);

	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}

void GestionMenus::imprimeMenuNuevaPartida()
{
	static CajaTexto c_nombrepartida({ 1, 3.75 }, { -6, 3.75 }, { -6,  2.75 }, { 1, 2.75 });
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	c_nombrepartida.dibuja();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("NUEVA PARTIDA", -8, 12);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Nombre de la partida:", -6, 4);

	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}

void GestionMenus::imprimeMenuRanking()
{
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	//c_volver.dibuja();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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

	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("RANKING PUNTUACIÓN", -15, 20);
	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}

void GestionMenus::imprimeMenuModo()
{
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	static CajaTexto c_inteligencia({ 2.5, 8.75 }, { -9, 8.75 }, { -9,  7.75 }, { 2.5, 7.75 });
	c_inteligencia.dibuja();
	static CajaTexto c_normal({ -5.5, 4.75 }, { -9, 4.75 }, { -9,  3.75 }, { -5.5, 3.75 });
	c_normal.dibuja();
	//c_volver.dibuja();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("MODO DE JUEGO", -11, 12);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Inteligiencia artificial", -9, 8);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Normal", -9, 4);

	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}

void GestionMenus::imprimeMenuJugador(int i)
{
	static CajaTexto c_nombrepartida({ 1, 3.75 }, { -6, 3.75 }, { -6,  2.75 }, { 1, 2.75 });
	c_nombrepartida.dibuja();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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
	if(i==1)
	{
		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::setFont(DIR_ALGER, 60);
		ETSIDI::printxy("JUGADOR 1", -11, 12);
	}
	if (i == 2)
	{
		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::setFont(DIR_ALGER, 60);
		ETSIDI::printxy("JUGADOR 2", -8, 12);
	}
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Nombre del jugador: ", -6, 4);
}

void GestionMenus::imprimeMenuSalas()
{
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	static CajaTexto c_crear({ -1.5, 8.75 }, { -9, 8.75 }, { -9,  7.75 }, { -1.5, 7.75 });
	//c_crear.dibuja();
	static CajaTexto c_unirse({ -0.5, 4.75 }, { -9, 4.75 }, { -9,  3.75 }, { -0.5, 3.75 });
	//c_unirse.dibuja();
	//c_volver.dibuja();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("MODO DE JUEGO", -11, 12);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Crear una Sala", -9, 8);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Unirse a una sala", -9, 4);

	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}

void GestionMenus::imprimeMenuNoExiste()
{
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	ETSIDI::setTextColor(1, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("EL ARCHIVO NO EXISTE", -14, 12);
	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}

void GestionMenus::imprimeMenuCrearSala()
{
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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
	ETSIDI::setFont(DIR_ALGER, 40);
	ETSIDI::printxy("Codigo de sala", -10, 12);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("0385726", -8, 8);
	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Usalo para conectarte en otro dispositivo", -12, 4);
	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}

void GestionMenus::imprimeMenuUnirseSala()
{
	static CajaTexto c_codigosala({ 1, 3.75 }, { -6, 3.75 }, { -6,  2.75 }, { 1, 2.75 });
	c_codigosala.dibuja();
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(RUTA_MENU).id);
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
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("UNIRSE A SALA", -8, 12);

	ETSIDI::setTextColor(0, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 20);
	ETSIDI::printxy("Codigo de sala:", -6, 4);

	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}

void GestionMenus::imprimeMenuNoEncontrado()
{
	static CajaTexto c_volver({ 29, -5.25 }, { 26, -5.25 }, { 26,  -6.25 }, { 29, -6.25 });
	ETSIDI::setTextColor(1, 0, 0);
	ETSIDI::setFont(DIR_ALGER, 60);
	ETSIDI::printxy("EL CODIGO NO ES CORRECTO", -16, 12);
	ETSIDI::setTextColor(0, 0, 1);
	ETSIDI::setFont(DIR_ALGER, 15);
	ETSIDI::printxy("Volver", 26, -6);
}
