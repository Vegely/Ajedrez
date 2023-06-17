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

enum TipoPieza { NONE, REY, DAMA, ALFIL, CABALLO, TORRE, PEON };

class Modelo : public Entity
{
private:
	Posicion	pos_coords;
	GLuint	    texture_ID;
	std::string model_path;
	std::string texture_path;
	TipoPieza   tipo_pieza;

public:
	const aiScene*   scene;
	Assimp::Importer importer;

public: 
	/* FORMA CANÓNICA */
	Modelo(void);
	Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, const std::string& model_path, const std::string& texture_path);
	Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, bool color);
	Modelo(TipoPieza tipo_pieza, const Point& initial_pos, bool color);
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

	/* SETTERS */
	void setCoords(const Posicion& pos)   { this->pos_coords   = pos; }
	void setModelPath  (std::string path) { this->model_path   = path; }
	void setTexturePath(std::string path) { this->texture_path = path; }
	void setTextureID  (GLuint ID)		  { this->texture_ID   = ID; }
	
	/* FUNCIONES */
	void render(void);
	void renderNodo(const aiNode* nodo);
	bool cargarTextura(void);
	void moverModelo(const Movimiento& movimiento);

	static TipoPieza castTipo(Pieza::tipo_t t);

	/* VARIABLES ESTÁTICAS */
	static std::string ruta_modelo_rey;
	static std::string ruta_modelo_dama;
	static std::string ruta_modelo_alfil;
	static std::string ruta_modelo_caballo;
	static std::string ruta_modelo_torre;
	static std::string ruta_modelo_peon;

	static std::string ruta_modelo_casillas_negras;
	static std::string ruta_modelo_casillas_blancas;
	static std::string ruta_modelo_marcos;
	static std::string ruta_modelo_letras;

	static std::string ruta_textura_blanco;
	static std::string ruta_textura_negro;
	static std::string ruta_textura_blanco_oscuro;
	static std::string ruta_textura_negro_claro;
	static std::string ruta_textura_marco;

	static std::string ruta_fondo;
};

#endif