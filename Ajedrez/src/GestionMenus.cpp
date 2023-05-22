#include "GestionMenus.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include <string>

void GestionMenus::imprimeMenuInicial() {
	float fscala = 100;
	gluLookAt(0, 7.5, 30, // posicion del ojo
		0.0, 7.5, 0.0, // hacia que punto mira (0,7.5,0) 
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y) 

	
	glTranslatef(-5, 20, 0);
	glScaled(1/fscala, 1/fscala, 1/fscala);
	for (char c : "AJEDREZ")
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);

	glTranslatef(-6*fscala, -5 * fscala, 0);
	for(char c: "Nueva partida")
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);

	glTranslatef(-8.5*fscala, -5 * fscala, 0);
	for (char c : "Cargar partida")
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);

	glTranslatef(-8*fscala, -5 * fscala, 0);
	for (char c : "Ranking")
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);

	glTranslatef(-4 * fscala, -5 * fscala, 0);
	for (char c : "Salir")
		glutStrokeCharacter(GLUT_STROKE_ROMAN, c);
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

