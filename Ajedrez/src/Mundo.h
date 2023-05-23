#pragma once
#include "Camera.h"
#include "Callbacks.h"
#include <vector>
#include "Partida.h"

struct Model
{
	const aiScene* scene;
	GLuint model_list;
	std::vector<GLuint> textures;
};


class Mundo
{
public:
	Camera camara;
	std::vector<Model> models;

	Mundo();

	void inicializa();
	void dibuja();
	void tecla(unsigned char key);
};

