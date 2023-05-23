#include "Caja.h"
#include "freeglut.h"


Caja::Caja(Vector2D ur, Vector2D ul, Vector2D dl, Vector2D dr) : ur(ur), ul(ul), dr(dr), dl(dl) {};

void Caja::dibuja() {
	glDisable(GL_LIGHTING);
	glColor3ub(255, 0, 0);
	glBegin(GL_POLYGON);
		glVertex3d(ur.x, ur.y, 0);
		glVertex3d(ul.x, ul.y, 0);
		glVertex3d(dl.x, dl.y, 0);
		glVertex3d(dr.x, dr.y, 0);
	glEnd();
	glEnable(GL_LIGHTING);
}