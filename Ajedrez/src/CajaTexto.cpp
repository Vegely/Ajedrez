#include "CajaTexto.h"
#include "freeglut.h"
#include "ETSIDI.h"
#include <cmath>
#include <iostream>

void CajaTexto::dibuja() {
	Caja::dibuja();
	glTranslatef((ur.x + 1.5*ul.x) / 2, (ur.y + dr.y) / 2, 1);
	
	ETSIDI::setTextColor(1, 1, 0);
	ETSIDI::setFont("gos.ttf", 16);
	//ETSIDI::printxy(texto.c_str(), ur.x, 8);

	glTranslatef(-(ur.x + 1.5*ul.x) / 2, -(ur.y + dr.y) / 2, -1);
}

bool CajaTexto::click(float x, float y) {
	//std::cout << x << "cosita" << std::endl;
	//std::cout << ANCHO_GL/*(abs(MAX_IZQD_GL - ul.x) / ANCHO_GL)*/ << " a ver que pasa" << std::endl;
	//std::cout << (float)glutGet(GLUT_WINDOW_WIDTH) << " que paso" << std::endl;
	
	if (x >= (abs(MAX_IZQD_GL - ul.x) * glutGet(GLUT_WINDOW_WIDTH) / ANCHO_GL) && x <= abs(MAX_IZQD_GL - ur.x) * glutGet(GLUT_WINDOW_WIDTH) / ANCHO_GL && 
		y >= (abs(MAX_ARRIBA_GL - ul.y) * glutGet(GLUT_WINDOW_HEIGHT) / ALTO_GL) && y <= (abs(MAX_ARRIBA_GL - dl.y) * glutGet(GLUT_WINDOW_HEIGHT) / ALTO_GL))
		return 1;
	else
	return 0;
}