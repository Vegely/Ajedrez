#include "Mundo.h"
#include "freeglut.h"
#include "Callbacks.h"

Mundo::Mundo()  {}

void Mundo::dibuja() {
	for (int i = 0; i < models.size(); i++)
	{
		glTranslatef(i * 10, 0, 0);
		glCallList(models[i].model_list);
		glTranslatef(-i * 10, 0, 0);
	}


	// Debug axis
	debugAxis();
}
