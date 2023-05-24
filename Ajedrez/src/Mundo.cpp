#include "Mundo.h"
#include "freeglut.h"
#include "Callbacks.h"

Mundo::Mundo() : camara({ 0.0f, 10.0f, 10.0f }, { 0 }) {

}

void Mundo::dibuja() {
	for (int i = 0; i < models.size(); i++)
	{
		glTranslatef(i * 10, 0, 0);
		glCallList(models[i].model_list);
		glTranslatef(-i * 10, 0, 0);
	}
	// Camera update
	camara.update();

	// Debug axis
	debugAxis();

	glTranslatef(0, 0, 0);
}
