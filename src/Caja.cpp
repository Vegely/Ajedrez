#include "Caja.h"
#include "freeglut.h"

Caja::Caja(float ulx, float uly, float drx, float dry)
{
	ul.x = ulx;
	ul.y = uly;
	dr.x = drx;
	dr.y = dry;
}

bool Caja::enCaja(float x, float y)
{
	if (x<dr.x && x>ul.x && y<ul.y && y>dr.y)
		return true;
	return false;
}

void Caja::dibuja()
{
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
	glVertex3f(ul.x, ul.y, 0);
	glVertex3f(dr.x, ul.y, 0);
	glVertex3f(dr.x, dr.y, 0);
	glVertex3f(ul.x, dr.y, 0);
	glEnd();
}