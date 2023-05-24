#include "Mundo.h"
#include "freeglut.h"
#include "Callbacks.h"

Mundo::Mundo() : camara_mundo({ 0.0f, 10.0f, 10.0f }, { 0 }) {}


void Mundo::dibuja() {
	for (int i = 0; i < models.size(); i++)
	{
		glTranslatef(i * 10, 0, 0);
		glCallList(models[i].model_list);
		glTranslatef(-i * 10, 0, 0);
	}
	// Camera update
	camara_mundo.update();

	// Debug axis
	debugAxis();
}
