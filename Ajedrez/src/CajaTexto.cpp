#include "CajaTexto.h"
#include "freeglut.h"
#include "ETSIDI.h"

void CajaTexto::dibuja() {
	float fscala = 100;

	Caja::dibuja();
	glTranslatef((ur.x + 1.5*ul.x) / 2, (ur.y + dr.y) / 2, 1);
	
	ETSIDI::setTextColor(1, 1, 0);
	ETSIDI::setFont("gos.ttf", 16);
	//ETSIDI::printxy(texto.c_str(), ur.x, 8);

	glTranslatef(-(ur.x + 1.5*ul.x) / 2, -(ur.y + dr.y) / 2, -1);
}

bool CajaTexto::click(float x, float y) {
	
	return 1;
}