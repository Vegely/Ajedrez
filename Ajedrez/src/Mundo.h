#pragma once
#include "Callbacks.h"
#include <vector>
#include "Partida.h"

struct Model
{
	GLuint model_list;
	std::vector<GLuint> textures;
};


class Mundo
{
public:
	std::vector<Model> models;

	Mundo();

	void inicializa();
	void dibuja();
	void tecla(unsigned char key);
};

