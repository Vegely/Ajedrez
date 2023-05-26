#ifndef MODELO_H
#define MODELO_H

// Librería gráfica
#include <freeglut.h>
// Librería de modelos 3D
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// Librería de texturas
#include <stb_image.h>
// Librerías de la STL
#include <string>
#include <iostream>
#include <vector>
// Librerías propias 
#include "Globals.h" // Clases útiles genéricas
#include "Hitbox.h"
#include "Movimiento.h"

enum TipoPieza { NONE, REY, DAMA, ALFIL, CABALLO, TORRE, PEON };

class Modelo : public Entity
{
private:
	GLuint	    texture_ID;
	std::string model_path;
	std::string texture_path;
	TipoPieza   tipo_pieza;
	Hitbox		hitbox;

public:
	const aiScene*   scene;
	Assimp::Importer importer;

public:
	/* FORMA CANÓNICA */
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
	void renderHitbox(void) { hitbox.render(); }
	bool cargarTextura(void);
};

#endif