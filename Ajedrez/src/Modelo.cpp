#include "Modelo.h"

Modelo::Modelo(const std::string& model_path, const std::string& texture_path, TipoPieza tipo_pieza) :
	texture_ID(0),
	model_path(model_path),
	texture_path(texture_path),
	tipo_pieza(tipo_pieza)
{
	this->scene = nullptr;
	this->scene = importer.ReadFile(this->model_path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (this->scene == nullptr || this->scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !this->scene->mRootNode)
	{
		std::cerr << "Failed to load model: " + model_path;
	}
	else
		std::cout << "Loaded " << scene->mNumMeshes << " meshes." << std::endl;
}

Modelo::Modelo(const Modelo& m)
{
	this->texture_ID   = m.texture_ID;
	this->model_path   = m.model_path;
	this->texture_path = m.texture_path;
	this->tipo_pieza   = m.tipo_pieza;
	this->scene = importer.ReadFile(this->model_path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mRootNode == nullptr) // Comprobación de lectura correcta del archivo.
		std::cerr << "Failed to load 3D model file: " << importer.GetErrorString();
}

Modelo& Modelo::operator = (const Modelo& rhs)
{ 
	this->scene		   = new aiScene;
	this->texture_ID   = rhs.texture_ID;
	this->model_path   = rhs.model_path;
	this->texture_path = rhs.texture_path;
	this->tipo_pieza   = rhs.tipo_pieza;
	return *this;
}

// Renderizado del modelo
void Modelo::render(const aiNode* nodo)
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

		// Enlaza la textura si está disponible
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
	// Renderiza los nodos hijos utilizando esta misma función hasta que no queden nodos hijos
	for (unsigned int i = 0; i < nodo->mNumChildren; i++)
		render(nodo->mChildren[i]);
}

bool Modelo::cargarTextura(void)
{
	int ancho, alto, num_componentes;
	unsigned char* datos_imagen = stbi_load(this->texture_path.c_str(), &ancho, &alto, &num_componentes, STBI_rgb);

	if (datos_imagen == nullptr)
	{
		std::cerr << "Failed to load texture file: " << this->texture_path.c_str();
		return false;
	}

	glGenTextures(1, &this->texture_ID);
	glBindTexture(GL_TEXTURE_2D, this->texture_ID);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, ancho, alto, GL_RGB, GL_UNSIGNED_BYTE, datos_imagen);

	stbi_image_free(datos_imagen);
	return true;
}