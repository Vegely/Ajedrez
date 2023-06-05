#ifndef MODELO_H
#define MODELO_H

// Librer�a gr�fica
#include <freeglut.h>
// Librer�a de modelos 3D
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// Librer�a de texturas
#include <stb_image.h>
// Librer�as de la STL
#include <string>
#include <iostream>
#include <vector>
// Librer�as propias 
#include "Globals.h" // Clases �tiles gen�ricas
#include "Entity.h"
#include "Movimiento.h"

enum TipoPieza { NONE, REY, DAMA, ALFIL, CABALLO, TORRE, PEON };

class Modelo : public Entity
{
private:
	GLuint	    texture_ID;
	std::string model_path;
	std::string texture_path;
	TipoPieza   tipo_pieza;

public:
	const aiScene*   scene;
	Assimp::Importer importer;

public: 
	/* FORMA CAN�NICA */
	Modelo(TipoPieza tipo_pieza, const Point& initial_pos, const std::string& model_path, const std::string& texture_path);
    virtual ~Modelo(void) { /*delete scene;*/ }
	Modelo(const Modelo& m);
	Modelo& operator = (const Modelo& rhs);

	/* GETTERS */
	std::string getModelPath    (void) const { return  this->model_path; }
	std::string getTexturePath  (void) const { return  this->texture_path; }
	aiScene     getSceneValue   (void) const { return *this->scene; }
	GLuint*     getTextureIDptr (void)		 { return &this->texture_ID; }
	aiNode&     getRootNode     (void) const { return *this->scene->mRootNode; }

	/* SETTERS */
	void setModelPath  (std::string path) { this->model_path   = path; }
	void setTexturePath(std::string path) { this->texture_path = path; }
	void setTextureID  (GLuint ID)		  { this->texture_ID   = ID; }
	void moverModelo(const Movimiento& movimiento);

	/* FUNCIONES */
	void render(void);
	void renderNodo(const aiNode* nodo);
	bool cargarTextura(void);
};

#endif