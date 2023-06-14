#include "Modelo.h"

Modelo::Modelo(void) :
	texture_ID(0),
	model_path(""),
	texture_path(""),
	tipo_pieza(NONE),
	scene(nullptr),
	Entity()
{ }

Modelo::Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, const std::string& model_path, const std::string& texture_path) :
	texture_ID(0),
	model_path(model_path),
	texture_path(texture_path),
	tipo_pieza(tipo_pieza),
	pos_coords(initial_pos),
	scene(nullptr),
	Entity(getPointFromCoords(initial_pos), Colors::White, "Modelo " + tipo_pieza)
{
	init();
}

Modelo::Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, bool color) :
	texture_ID(0),
	model_path(""),
	texture_path(""),
	tipo_pieza(tipo_pieza),
	pos_coords(initial_pos),
	scene(nullptr),
	Entity(getPointFromCoords(initial_pos), Colors::White, "Modelo " + tipo_pieza)
{
	switch (tipo_pieza)
	{
	case REY:
		model_path = Modelo::ruta_modelo_rey;
		break;

	case DAMA:
		model_path = Modelo::ruta_modelo_dama;
		break;

	case ALFIL:
		model_path = Modelo::ruta_modelo_alfil;
		break;

	case CABALLO:
		model_path = Modelo::ruta_modelo_caballo;
		break;

	case TORRE:
		model_path = Modelo::ruta_modelo_torre;
		break;

	case PEON:
		model_path = Modelo::ruta_modelo_peon;
		break;

	default:
		std::cerr << "No default model path for the specified type." << std::endl;
		exit(0);
		break;
	}
	if (color)
		texture_path = Modelo::ruta_textura_blanco;
	else
		texture_path = Modelo::ruta_textura_negro;

	init();
}

void Modelo::init(void)
{
	this->scene = importer.ReadFile(this->model_path, aiProcess_Triangulate
		| aiProcess_OptimizeMeshes
		| aiProcess_JoinIdenticalVertices
		| aiProcess_Triangulate
		| aiProcess_CalcTangentSpace
		| aiProcess_FlipUVs);
	if (this->scene == nullptr || this->scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->scene->mRootNode)
	{
		std::cerr << "Failed to load model: " + model_path;
	}
	else
		std::cout << "Created meshes for model type " << tipo_pieza << "." << std::endl;

	if (this->tipo_pieza == NONE)
		this->position = Point{ 0, 0, 0 };
}

Modelo::Modelo(const Modelo& m)
{
	this->position = m.position;
	this->velocity = m.velocity;
	this->acceleration = m.acceleration;
	this->texture_ID   = m.texture_ID;
	this->model_path   = m.model_path;
	this->texture_path = m.texture_path;
	this->tipo_pieza   = m.tipo_pieza;
	this->scene = importer.ReadFile(this->model_path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mRootNode == nullptr) // Comprobaci�n de lectura correcta del archivo.
		std::cerr << "Failed to load 3D model file: " << importer.GetErrorString();
}

Modelo& Modelo::operator = (const Modelo& rhs)
{
	this->position = rhs.position;
	this->velocity = rhs.velocity;
	this->acceleration = rhs.acceleration;
	this->texture_ID = rhs.texture_ID;
	this->model_path = rhs.model_path;
	this->texture_path = rhs.texture_path;
	this->tipo_pieza = rhs.tipo_pieza;
	this->scene = importer.ReadFile(this->model_path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mRootNode == nullptr) // Comprobacion de lectura correcta del archivo.
		std::cerr << "Failed to load 3D model file: " << importer.GetErrorString();

	return *this;
}

// Renderizado del modelo
void Modelo::renderNodo(const aiNode* nodo)
{
	if (nodo == nullptr)
	{
		std::cerr << "The rendering base node is a nullptr." << std::endl;
		return;
	}

	for (unsigned int i = 0; i < nodo->mNumMeshes; i++)
	{
		const aiMesh*     mesh     = scene->mMeshes[nodo->mMeshes[i]];
		const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// Aplica las propiedades del material.
		aiColor4D difusion_color;
		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &difusion_color))
			glColor4f(difusion_color.r, difusion_color.g, difusion_color.b, difusion_color.a);

		// Enlaza la textura si est� disponible
		if (mesh->HasTextureCoords(0) && texture_ID != 0)
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture_ID);
		}
		else glDisable(GL_TEXTURE_2D);

		// Dibuja las caras del mesh
		glBegin(GL_TRIANGLES);
		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
		{
			const aiFace& cara = mesh->mFaces[j];
			for (unsigned int k = 0; k < cara.mNumIndices; k++)
			{
				unsigned int indice = cara.mIndices[k];
				if (mesh->HasTextureCoords(0))
				{
					const aiVector3D& coordenada_textura = mesh->mTextureCoords[0][indice];
					glTexCoord2f(coordenada_textura.x, coordenada_textura.y);
				}
				const aiVector3D& vertice = mesh->mVertices[indice];
				glVertex3f(vertice.x, vertice.y, vertice.z);
			}
		}
		glEnd();
	}
	// Renderiza los nodos hijos utilizando esta misma funcion hasta que no queden nodos hijos
	for (unsigned int i = 0; i < nodo->mNumChildren; i++)
		renderNodo(nodo->mChildren[i]);
}

void Modelo::render(void)
{
	if (this->scene == nullptr)
		return;

	//glDisable(GL_LIGHTING);

	if (this->tipo_pieza != NONE)
		this->position = getPointFromCoords(this->pos_coords);

	glTranslatef(this->position.x,  this->position.y,  this->position.z);
		glRotatef(-90, 1, 0, 0);
		renderNodo(this->scene->mRootNode);
		glRotatef(90, 1, 0, 0);
	glTranslatef(-this->position.x, -this->position.y, -this->position.z);
	
	
	//glEnable(GL_LIGHTING);
}

bool Modelo::cargarTextura(void)
{
	if (this->scene == nullptr)
		return false;

	int ancho, alto, num_componentes;

	glGenTextures(1, &this->texture_ID);
	if (this == nullptr)
	{
		std::cerr << "Error binding texture to object." << std::endl;
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, this->texture_ID);

	unsigned char* datos_imagen = stbi_load(this->texture_path.c_str(), &ancho, &alto, &num_componentes, STBI_rgb);

	if (datos_imagen == nullptr)
	{
		std::cerr << "Failed to load texture file: " << this->texture_path.c_str();
		return false;
	}

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, ancho, alto, GL_RGB, GL_UNSIGNED_BYTE, datos_imagen);

	stbi_image_free(datos_imagen);
	std::cout << "Texture binded." << std::endl;
	return true;
}

void Modelo::moverModelo(const Movimiento& movimiento)
{
	if (movimiento.inicio == this->pos_coords && this->tipo_pieza != NONE)
	{
		//std::cout << "Modelo tipo " << this->tipo_pieza << " movido de la posicion " << pos_coords.x << pos_coords.y;
		this->pos_coords = movimiento.fin;
		//std::cout << " a la posicion " << pos_coords.x << pos_coords.y << ". " << std::endl;
	}
}

TipoPieza Modelo::castTipo(Pieza::tipo_t t)
{
	switch (t)
	{
	case Pieza::tipo_t::REY:
		return REY;
		break;

	case Pieza::tipo_t::DAMA:
		return DAMA;
		break;

	case Pieza::tipo_t::ALFIL:
		return ALFIL;
		break;

	case Pieza::tipo_t::CABALLO:
		return CABALLO;
		break;

	case Pieza::tipo_t::TORRE:
		return TORRE;
		break;

	case Pieza::tipo_t::PEON:
		return PEON;
		break;

	default:
		break;
	}
}

std::string Modelo::ruta_modelo_rey = "modelos/rey.obj";
std::string Modelo::ruta_modelo_dama = "modelos/dama.obj";
std::string Modelo::ruta_modelo_alfil = "modelos/alfil.obj";
std::string Modelo::ruta_modelo_caballo = "modelos/caballo.obj";
std::string Modelo::ruta_modelo_torre = "modelos/torre.obj";
std::string Modelo::ruta_modelo_peon = "modelos/peon.obj";

std::string Modelo::ruta_modelo_casillas_negras = "modelos/casillas_negras.obj";
std::string Modelo::ruta_modelo_casillas_blancas = "modelos/casillas_blancas.obj";
std::string Modelo::ruta_modelo_marcos = "modelos/marcos.obj";
std::string Modelo::ruta_modelo_letras = "modelos/letras.obj";

std::string Modelo::ruta_textura_blanco = "texturas/marmol_blanco.jpg";
std::string Modelo::ruta_textura_negro = "texturas/marmol_negro.jpg";
std::string Modelo::ruta_textura_blanco_oscuro = "texturas/marmol_blanco_oscuro.jpg";
std::string Modelo::ruta_textura_negro_claro = "texturas/marmol_negro_claro.jpg";
std::string Modelo::ruta_textura_marco = "texturas/marmol_negro_marco.jpg";

std::string Modelo::ruta_fondo = "texturas/espacio.png";