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

struct Textura
{
	int			   ancho;
	int			   alto;
	int			   num_componentes;
	unsigned char* datos_imagen;
	GLuint		   ID;
	std::string    ruta;
	Textura(std::string ruta) : ancho(), alto(), num_componentes(), datos_imagen(), ID(), ruta(ruta) { }
};

struct ModeloBase
{
	const aiScene* scene;
	Assimp::Importer importer;

	void init(std::string path)
	{
		this->scene = importer.ReadFile(path,
			aiProcess_Triangulate
			| aiProcess_OptimizeMeshes
			| aiProcess_JoinIdenticalVertices
			| aiProcess_CalcTangentSpace
			| aiProcess_FlipUVs);
		if (this->scene == nullptr || this->scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->scene->mRootNode)
			std::cerr << "Failed to load model at " + path << std::endl;
	}

	ModeloBase& operator = (const ModeloBase& rhs)
	{
		this->scene = rhs.scene;
	}
};

struct ModeloTexturizado
{
	ModeloBase* modelo;
	Textura textura;

	ModeloTexturizado(std::string path) : modelo(new ModeloBase()), textura(path) {}
	~ModeloTexturizado(void) { delete modelo; }
	void init(ModeloBase* modelo_base)
	{
		this->modelo = modelo_base;

		if (modelo == nullptr)
		{
			std::cerr << "Error binding texture to object." << std::endl;
			return;
		}
		if (modelo->scene == nullptr) return;

		glGenTextures(1, &textura.ID);
		glBindTexture(GL_TEXTURE_2D, textura.ID);

		textura.datos_imagen = stbi_load(textura.ruta.c_str(), &textura.ancho, &textura.alto, &textura.num_componentes, STBI_rgb);

		if (textura.datos_imagen == nullptr)
		{
			std::cerr << "Failed to load texture file: " << textura.ruta.c_str() << std::endl;
			return;
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, textura.ancho, textura.alto, GL_RGB, GL_UNSIGNED_BYTE, textura.datos_imagen);

		stbi_image_free(textura.datos_imagen);

		std::cout << "Texture loaded." << std::endl;
	}
};

class Modelo : public Entity
{
private:
	Posicion	pos_coords;
	std::string model_path;
	std::string texture_path;
	TipoPieza   tipo_pieza;
	bool		color;

public:
	ModeloTexturizado* modelo_texturizado;

public: 
	/* FORMA CANÓNICA */
	Modelo(void);
	Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, ModeloTexturizado* modelo_texturizado, bool color = false);
	Modelo(TipoPieza tipo_pieza, const Point& initial_pos, const std::string& model_path, const std::string& texture_path);
	virtual ~Modelo(void) { }

	/* INICIALIZACIÓN */
	void init(void);
	void initRutas(void);

	/* GETTERS */
	Posicion	getCoords	    (void) const { return this->pos_coords; }
	std::string getModelPath    (void) const { return this->model_path; }
	std::string getTexturePath  (void) const { return this->texture_path; }
	TipoPieza   getTipo			(void) const { return this->tipo_pieza; }
	bool		getColor		(void) const { return this->color; }
	ModeloTexturizado* getModeloTexturizado(void) { return this->modelo_texturizado; }

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

#endif