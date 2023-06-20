#ifndef MODELO_H
#define MODELO_H

// Libreria grafica
#include <freeglut.h>
// Libreria de modelos 3D
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// Libreria de texturas
#include <stb_image.h>
// Librerias de la STL
#include <string>
#include <iostream>
#include <vector>
// Librerias propias 
#include "Entity.h"
#include "Movimiento.h"
#include "Pieza.h"

enum TipoPieza { NONE, REY, DAMA, ALFIL, CABALLO, TORRE, PEON, OBJETO };

class Modelo : public Entity
{
private:
	Posicion	pos_coords;
	GLuint	    texture_ID;
	std::string model_path;
	std::string texture_path;
	TipoPieza   tipo_pieza;
	bool color;

public:
	const aiScene*   scene;
	Assimp::Importer importer;

public: 
	/* FORMA CANÓNICA */
	Modelo(void);
	Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, const std::string& model_path, const std::string& texture_path);
	Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, bool color);
	Modelo(TipoPieza tipo_pieza, const Point& initial_pos, bool color);
	Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, bool color, const aiScene* scene);
	Modelo(const Posicion& initial_pos, const aiScene* scene, std::string texture_path);
	virtual ~Modelo(void) { }
	Modelo(const Modelo& m);
	Modelo& operator = (const Modelo& rhs);
	/* INICIALIZACIÓN */
	void init(void);

	/* GETTERS */
	Posicion	getCoords	    (void) const { return  this->pos_coords; }
	std::string getModelPath    (void) const { return  this->model_path; }
	std::string getTexturePath  (void) const { return  this->texture_path; }
	aiScene     getSceneValue   (void) const { return *this->scene; }
	GLuint*     getTextureIDptr (void)		 { return &this->texture_ID; }
	aiNode&     getRootNode     (void) const { return *this->scene->mRootNode; }
	TipoPieza   getTipo			(void) const { return  this->tipo_pieza; }
	bool		getColor		(void) const { return  this->color; }

	/* SETTERS */
	void setCoords(const Posicion& pos) { this->pos_coords = pos; }
	
	/* FUNCIONES */
	void render(void);
	void renderNodo(const aiNode* nodo);
	bool cargarTextura(void);
	bool moverModelo(const Movimiento& movimiento);

	static TipoPieza castTipo(Pieza::tipo_t t);
	static Pieza::tipo_t castTipo(TipoPieza t);
};

struct ModeloBase
{
	const aiScene* scene;
	Assimp::Importer importer;
	void init(std::string path)
	{
		this->scene = importer.ReadFile(path, aiProcess_Triangulate
			| aiProcess_OptimizeMeshes
			| aiProcess_JoinIdenticalVertices
			| aiProcess_Triangulate
			| aiProcess_CalcTangentSpace
			| aiProcess_FlipUVs);
		if (this->scene == nullptr || this->scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->scene->mRootNode)
			std::cerr << "Failed to load model at " + path;
		else
			std::cout << "Created meshes." << std::endl;
	}
};

#endif