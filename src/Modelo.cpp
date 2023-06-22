#include "Modelo.h"
#include "Mundo.h"

Modelo::Modelo(void) :
	model_path(""),
	texture_path(""),
	tipo_pieza(NONE),
	modelo_texturizado(nullptr),
	color(false),
	Entity()
{ }

Modelo::Modelo(TipoPieza tipo_pieza, const Point& initial_pos, const std::string& model_path, const std::string& texture_path) :
	model_path(model_path),
	texture_path(texture_path),
	tipo_pieza(tipo_pieza),
	pos_coords(Posicion()),
	modelo_texturizado(new ModeloTexturizado(texture_path)),
	color(false),
	Entity((initial_pos), "Modelo " + tipo_pieza)
{
	cargarVertices();
}

Modelo::Modelo(TipoPieza tipo_pieza, const Posicion& initial_pos, ModeloTexturizado* modelo_texturizado, bool color) :
	model_path(""),
	texture_path(""),
	tipo_pieza(tipo_pieza),
	pos_coords(initial_pos),
	modelo_texturizado(modelo_texturizado),
	color(color),
	Entity(getPointFromCoords(initial_pos), "Modelo " + tipo_pieza)
{
	
}

Modelo::Modelo(TipoPieza tipo_pieza, const Point& initial_pos, ModeloTexturizado* modelo_texturizado, bool color) :
	model_path(""),
	texture_path(""),
	tipo_pieza(tipo_pieza),
	pos_coords(Posicion()),
	modelo_texturizado(modelo_texturizado),
	color(color),
	Entity(initial_pos, "Modelo " + tipo_pieza)
{

}

void Modelo::cargarVertices(void)
{
	this->modelo_texturizado->modelo->scene = this->modelo_texturizado->modelo->importer.ReadFile(this->model_path,
		  aiProcess_OptimizeMeshes
		| aiProcess_JoinIdenticalVertices
		| aiProcess_Triangulate
		| aiProcess_CalcTangentSpace
		| aiProcess_FlipUVs);
	if (this->modelo_texturizado->modelo->scene == nullptr
		|| this->modelo_texturizado->modelo->scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
		|| !this->modelo_texturizado->modelo->scene->mRootNode)
		std::cerr << "Failed to load model: " + model_path;

	if (this->tipo_pieza == NONE)
		this->position = Point{ 0, 0, 0 };
}

void Modelo::initRutas(void)
{
	switch (this->tipo_pieza)
	{
	case REY:
		this->model_path = ruta_modelo_rey;
		break;

	case DAMA:
		this->model_path = ruta_modelo_dama;
		break;

	case ALFIL:
		this->model_path = ruta_modelo_alfil;
		break;

	case CABALLO:
		this->model_path = ruta_modelo_caballo;
		break;

	case TORRE:
		this->model_path = ruta_modelo_torre;
		break;

	case PEON:
		this->model_path = ruta_modelo_peon;
		break;

	default:
		std::cerr << "No default model path for the specified type." << std::endl;
		exit(0);
		break;
	}
	if (color)
		this->texture_path = ruta_textura_blanco;
	else
		this->texture_path = ruta_textura_negro;
}

void Modelo::renderNodo(const aiNode* nodo)
{
	// Comprobacion de errores
	if (nodo == nullptr) { std::cerr << "The rendering base node is a nullptr." << std::endl; return; }

//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, this->modelo_texturizado->textura.ID);
//
//	for (unsigned int i = 0; i < nodo->mNumMeshes; i++)
//	{
//		const aiMesh* mesh = this->modelo_texturizado->modelo->scene->mMeshes[nodo->mMeshes[i]];
//		const aiMaterial* material = this->modelo_texturizado->modelo->scene->mMaterials[mesh->mMaterialIndex];
//
//		// Aplica las propiedades del material.
//		aiColor4D difusion_color;
// 		if (AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &difusion_color))
//			glColor4f(difusion_color.r, difusion_color.g, difusion_color.b, difusion_color.a);
//
//		// Enlaza la textura si esta disponible
//		if (mesh->HasTextureCoords(0) && this->modelo_texturizado->textura.ID != 0)
//		{
//			glEnable(GL_TEXTURE_2D);
//			glBindTexture(GL_TEXTURE_2D, this->modelo_texturizado->textura.ID);
//		}
//		else glDisable(GL_TEXTURE_2D);
//
//		// Dibuja las caras del mesh
//		glBegin(GL_TRIANGLES);
//		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
//		{
//			const aiFace& cara = mesh->mFaces[j];
//			for (unsigned int k = 0; k < cara.mNumIndices; k++)
//			{
//				unsigned int indice = cara.mIndices[k];
//				if (mesh->HasNormals())
//				{
//					const aiVector3D& normales = mesh->mNormals[indice];
//					glNormal3f(normales.x, normales.y, normales.z);
//				}
//				if (mesh->HasTextureCoords(0)) {
//					const aiVector3D& texCoord = mesh->mTextureCoords[0][indice];
//					glTexCoord2f(texCoord.x, texCoord.y);
//				}
//				const aiVector3D& vertice = mesh->mVertices[indice];
//				glVertex3f(vertice.x, vertice.y, vertice.z);
//			}
//		}
//		glEnd();
//	}
//	// Renderiza los nodos hijos utilizando esta misma funcion hasta que no queden nodos hijos
//	for (unsigned int i = 0; i < nodo->mNumChildren; i++)
//		renderNodo(nodo->mChildren[i]);

	for (unsigned int i = 0; i < nodo->mNumMeshes; i++)
	{
		const aiMesh* mesh = this->modelo_texturizado->modelo->scene->mMeshes[nodo->mMeshes[i]];

		glBegin(GL_TRIANGLES);

		for (unsigned int j = 0; j < mesh->mNumFaces; j++)
		{
			const aiFace& cara = mesh->mFaces[j];
			for (unsigned int k = 0; k < cara.mNumIndices; k++)
			{
				unsigned int indice = cara.mIndices[k];
				if (mesh->HasNormals())
				{
					const aiVector3D& normales = mesh->mNormals[indice];
					glNormal3f(normales.x, normales.y, normales.z);
				}
				if (mesh->HasTextureCoords(0))
				{
					const aiVector3D& coords_textura = mesh->mTextureCoords[0][indice];
					glTexCoord2f(coords_textura.x, coords_textura.y);
				}
				const aiVector3D& vertices = mesh->mVertices[indice];
				glVertex3f(vertices.x, vertices.y, vertices.z);
			}
		}
		glEnd();
	}

	for (unsigned int i = 0; i < nodo->mNumChildren; ++i) {
		renderNodo(nodo->mChildren[i]);
	}
}

void Modelo::render(void)
{
	// Comprobacion de que el modelo sea renderizable.
	if (this->modelo_texturizado->modelo->scene == nullptr) return;
	// Asignacion de coordenadas de OpenGL segun la posicion.
	if (this->tipo_pieza != NONE)
	{
		if (this->pos_coords != Posicion())
			this->position = getPointFromCoords(this->pos_coords);
		else
			this->position = Point{ 0, 100, 0 };
	}

	// Enlazado de la textura.
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->modelo_texturizado->textura.ID);

	// Renderizacion del modelo.
	glPushMatrix();
	glTranslatef(this->position.x,  this->position.y,  this->position.z);
	{
		glRotatef(-90, 1, 0, 0);
		{
			if (this->tipo_pieza != NONE) glRotatef(-90, 0, 0, 1);
				renderNodo(this->modelo_texturizado->modelo->scene->mRootNode);
			if (this->tipo_pieza != NONE) glRotatef(90, 0, 0, 1);
		}
		glRotatef(90, 1, 0, 0);
	}
	glTranslatef(-this->position.x, -this->position.y, -this->position.z);
	glPopMatrix();
}

bool Modelo::cargarTextura(void)
{
	if (this->modelo_texturizado->modelo->scene == nullptr)
		return false;

	int ancho, alto, num_componentes;

	glGenTextures(1, &this->modelo_texturizado->textura.ID);
	if (this == nullptr)
	{
		std::cerr << "Error binding texture to object." << std::endl;
		return false;
	}
	glBindTexture(GL_TEXTURE_2D, this->modelo_texturizado->textura.ID);

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

	return true;
}

bool Modelo::moverModelo(const Movimiento& movimiento)
{
	if (movimiento.inicio == this->pos_coords && this->tipo_pieza != NONE)
	{
		this->pos_coords = movimiento.fin;
		return true;
	}
	else
		return false;
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

	case Pieza::tipo_t::NULA:
		return NONE;
		break;

	default:
		break;
	}
}

Pieza::tipo_t Modelo::castTipo(TipoPieza t)
{
	switch (t)
	{
	case REY:
		return Pieza::tipo_t::REY;
		break;

	case DAMA:
		return Pieza::tipo_t::DAMA;
		break;

	case ALFIL:
		return Pieza::tipo_t::ALFIL;
		break;

	case CABALLO:
		return Pieza::tipo_t::CABALLO;
		break;

	case TORRE:
		return Pieza::tipo_t::TORRE;
		break;

	case PEON:
		return Pieza::tipo_t::PEON;
		break;
		
	case NONE:
		return Pieza::tipo_t::NULA;
		break;

	default:
		break;
	}
}

void ModeloBase::cargarModelo(std::string path)
{
	this->scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_FlipUVs);
	if (this->scene == nullptr || this->scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->scene->mRootNode)
	{
		std::cerr << "Error loading model: " << importer.GetErrorString() << std::endl;
		return;
	}
}

void ModeloTexturizado::cargarTextura(ModeloBase* modelo_base)
{
	// Gestion del modelo base.
	this->modelo = modelo_base;
	if (modelo == nullptr)		  { std::cerr << "Error binding texture to object." << std::endl; return; }
	if (modelo->scene == nullptr) { std::cerr << "Error binding texture to object." << std::endl; return; }

	// Carga de los datos de la textura.
	textura.datos_imagen = stbi_load(textura.ruta.c_str(), &textura.ancho, &textura.alto, &textura.num_componentes, STBI_rgb);

	// Gestion de errores
	if (textura.datos_imagen == nullptr) { std::cerr << "Failed to load texture file: " << textura.ruta.c_str() << std::endl; return; }
	
	// Generacion de la textura y carga del ID.
	glGenTextures(1, &textura.ID);
	glBindTexture(GL_TEXTURE_2D, textura.ID);
	
	// Carga de la textura y parametros de esta.
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textura.ancho, textura.alto, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.datos_imagen);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, textura.ancho, textura.alto, GL_RGB, GL_UNSIGNED_BYTE, textura.datos_imagen);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Liberacion del puntero de la textura y limpieza del bit GL_TEXTURE_2D.
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(textura.datos_imagen);
}