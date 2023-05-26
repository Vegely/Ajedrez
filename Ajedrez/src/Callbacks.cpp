// Callbacks.cpp | Source file for callback functions called by GLUT

#include "Callbacks.h"
#include <fstream>
#include <sstream>
#include "CoordinadorAjedrez.h"

CoordinadorAjedrez ajedrez;

/*
// Rutas de las texturas.
std::vector<std::string> texture_paths = { "texturas/rocks.tga", "texturas/rocks.tga" };

GLuint loadTexture(const std::string& file_path)
{
	GLuint textureID; // Crea un ID para la textura
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID); // Añade el ID a una textura de OpenGL

	// Prepara los parámetros de la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Carga la imagen de la textura y hace una comprobación de errores.
	std::ifstream file(file_path, std::ios::binary);
	if (!file)
	{
		std::cerr << "Failed to load texture: " << file_path << std::endl;
		glDeleteTextures(1, &textureID);
		return 0;
	}
	else
	{
		std::cout << "Texture file loaded successfully." << std::endl;
	}

	// Lee la cabecera del archivo TGA (1 byte)
	char header[18];
	file.read(header, 18);

	// Con los datos leídos, comprueba si el archivo es RGB o RGBA
	bool isRGB = header[2] == 2;
	bool isRGBA = header[2] == 3;
	// Si no es ninguno de ellos el formato leído no es válido
	if (!isRGB && !isRGBA) {
		std::cerr << "Invalid TGA format in texture: " << file_path << std::endl;
		glDeleteTextures(1, &textureID);
		return 0;
	}
	// Asigna las dimensiones de la textura a variables temporales.
	int width = header[12] + (header[13] << 8);
	int height = header[14] + (header[15] << 8);
	int bpp = header[16] / 8;
	// Crea un vector de bytes del tamaño del área de la imagen por los bytes por píxel de la textura.
	std::vector<byte> imageData(width * height * bpp);

	if (isRGB)
	{
		// Si está en formato RGB, bpp = 3, por lo que reduce el tamaño del array.
		// reinterpret_cast es un cast en tiempo de compilación.
		file.read(reinterpret_cast<char*>(imageData.data()), width * height * 3);
		std::cout << "Texture file '" << file_path << "' is in RGB format." << std::endl;
	}
	else if (isRGBA)
	{
		// Si está en formato RGBA, bpp = 4.
		// Crea un vector temporal con la dimensión apropiada y luego reduce el tamaño del array base.
		std::vector<byte> temp(width * height * 4);
		file.read(reinterpret_cast<char*>(temp.data()), width * height * 4);

		// Convierte los datos en RGBA a RGB y los introduce en el vector temporal para luego reordenarlos.
		for (int i = 0; i < width * height; ++i)
		{
			imageData[i * 3] = temp[i * 4];
			imageData[i * 3 + 1] = temp[i * 4 + 1];
			imageData[i * 3 + 2] = temp[i * 4 + 2];
		}
		std::cout << "Texture file '" << file_path << "' is in RGBA format." << std::endl;
	}

	// Crea la textura.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData.data());
	// Devuelve el ID de la textura.
	return textureID;
}

void importModel(const char* file_path)
{
	// Crea una instancia del importer de Assimp para cargar y evaluar el archivo de textura.
	Assimp::Importer importer; // Instancia del objeto que importa los modelos y los lee.
	GLuint model_list = 0; // Indica qué número de lista es la usada.
	const aiScene* scene = importer.ReadFile(file_path, // Puntero constante con la info. de la textura.
		aiProcess_CalcTangentSpace		|
		aiProcess_Triangulate			|
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	std::vector<GLuint> textures; // Vector para cargar las texturas en el modelo.
	// Comprobación de errores
	if (!scene)
	{
		std::cerr << "Failed to load model: " << importer.GetErrorString() << std::endl;
		return;
	}
	else
	{
		std::cout << "Model loaded succesfully." << std::endl;
	}

	// Crea una lista de visualización (píxeles) para el modelo.
	model_list = glGenLists(1);
	glNewList(model_list, GL_COMPILE);

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		const aiMesh* mesh = scene->mMeshes[i]; // Se copia el contenido del archivo para evaluar sus materiales.
		const aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		// Prepara las propiedades de los materiales
		aiColor3D ambientColor, diffuseColor, specularColor;
		material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor);
		material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor);
		glMaterialfv(GL_FRONT, GL_AMBIENT, &(ambientColor.r));
		glMaterialfv(GL_FRONT, GL_DIFFUSE, &(diffuseColor.r));
		glMaterialfv(GL_FRONT, GL_SPECULAR, &(specularColor.r));

		// Carga y enlaza las texturas
		for (int j = 0; j < material->GetTextureCount(aiTextureType_DIFFUSE); j++)
		{
			aiString path;
			material->GetTexture(aiTextureType_DIFFUSE, j, &path);

			std::string full_path = texture_paths[j] + path.C_Str(); // texture_paths es global en este archivo.
			GLuint textureID = loadTexture(full_path);

			textures.push_back(textureID);
		}

		// Renderiza el mesh
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			const aiFace& face = mesh->mFaces[j];
			for (int k = 0; k < face.mNumIndices; k++)
			{
				const aiVector3D& vertex = mesh->mVertices[face.mIndices[k]];
				const aiVector3D& normal = mesh->mNormals[face.mIndices[k]];
				if (mesh->HasTextureCoords(0))
				{
					const aiVector3D& texCoord = mesh->mTextureCoords[0][k];
					glTexCoord2f(texCoord.x, texCoord.y);
				}
				glNormal3f(normal.x, normal.y, normal.z);
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}
		}
		glEnd();

		// Limpia las texturas para cargar las siguentes
		for (const auto& texture : textures)
		{
			glDeleteTextures(1, &texture);
		}
	}
	glEndList();

	ajedrez.mundo.models.push_back({ scene, model_list, textures });
}*/

void graphicsInit(int* argc, char** argv)
{
	
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("FlatChess");
	//habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutTimerFunc(25, OnTimer, 0); // Each 25 ms, the function will call OnTimer(); 
	glutKeyboardFunc(OnKeyboardDown);
	glutKeyboardUpFunc(OnKeyboardUp);
	glutSpecialFunc(OnKeyboardSpecial);
	glutMouseFunc(OnMouseClick);
	glutPassiveMotionFunc(OnMouseMotion);
	//glutSpecialFunc(onSpecialKeyboardDown);
	/*
	// Initialize GLUT and create a window
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("FlatChess");

	// Importa los modelos 3D.
	importModel("modelos/rey_blender_2.obj");
	importModel("modelos/teapot.obj");

	// Set up the OpenGL state
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL_FACE);

	// Set up the camera and viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		ajedrez.mundo.camara.getPosition().x, ajedrez.mundo.camara.getPosition().y, ajedrez.mundo.camara.getPosition().z,
		ajedrez.mundo.camara.getLookAt().x, ajedrez.mundo.camara.getLookAt().y, ajedrez.mundo.camara.getLookAt().z,
		0.0f, 1.0f, 0.0f);
	glViewport(0, 0, 1920, 1080);

	// Callback registering
	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutTimerFunc(25, OnTimer, 0); // Each 25 ms, the function will call OnTimer(); 
	glutKeyboardFunc(OnKeyboardDown);
	glutKeyboardUpFunc(OnKeyboardUp);
	glutSpecialFunc(OnKeyboardSpecial);
	glutMouseFunc(OnMouseClick);
	glutPassiveMotionFunc(OnMouseMotion);*/


	glutMainLoop();
}

// Continuously draws what it is specified to it.
void OnDraw(void)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3ub(255,0, 0);
	glutSolidCube(0.1f);

	ajedrez.dibuja();


	glutSwapBuffers();
	//ajedrez.dibuja();
}

// Reshapes the window if needed without resizing the objects and mantaining their proportions.
void OnReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

// Each set time, performs the set functions.
void OnTimer(int value)
{
	ajedrez.onTimer();
	glutTimerFunc(25, OnTimer, 0);
}

void OnKeyboardDown(const unsigned char key, int x_t, int y_t)
{
	ajedrez.tecla(key);
}


void OnKeyboardUp(const unsigned char key, int x, int y)
{

	// End of keyboard reading code (do not erase or write anything afterwardas).
	//glutPostRedisplay();
}

void OnKeyboardSpecial(int key, int x, int y)
{
	ajedrez.teclaEspecial(key);
	// End of keyboard reading code (do not erase or write anything afterwardas).
	//glutPostRedisplay();
}

// 0 == left, 1 == middle, 2 == right, 3 == scroll up, 4 == scroll down.
void OnMouseClick(int button, int state, int x, int y)
{
	ajedrez.click(button, state, x, y);
	//ajedrez.click(button, state, x, y);
	/*static std::string btn;
	switch (button)
	{
	case 0:
		btn = "left";
		break;
	case 1:
		btn = "middle";
		break;
	case 2:
		btn = "right";
		break;
	case 3:
		btn = "scroll up";
		break;
	case 4:
		btn = "scroll down";
		break;
	default:
		break;
	}
	*/
	//if (state == GLUT_DOWN)
	//{
	//	std::cout << "Button: " << btn << std::endl;
	//	std::cout << "X:" << x << std::endl;
	//	std::cout << "Y:" << y << std::endl;
	//}

	// End of mouse reading code (do not erase or write anything afterwards).
	//glutPostRedisplay();
}

void OnMouseMotion(int x, int y)
{

}

void debugAxis(void)
{
	// Debug: reference axis:
	glTranslatef(25000, 25000, 25000);
	glColor3f(255, 255, 255);
	glutWireCube(50000);
	glTranslatef(-25000, -25000, -25000);

	glTranslatef(5, 0, 0);
	glRotatef(90, 0, 1, 0);
	glRotatef(-90, 0, 0, 1);
	glColor3f(255, 255, 255);
	glutSolidCone(.3f, .7f, 10, 10); // X axis.
	glRotatef(90, 0, 0, 1);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(-5, 0, 0);

	for (float i = 0; i < 500; i++)
	{
		glTranslatef(i, 0, 0);
		glColor3f(255, 255, 255);
		glutSolidCube(.2f);
		glTranslatef(-i, 0, 0);

		glTranslatef(0, i, 0);
		glColor3f(255, 255, 255);
		glutSolidCube(.2f);
		glTranslatef(0, -i, 0);

		glTranslatef(0, 0, i);
		glColor3f(255, 255, 255);
		glutSolidCube(.2f);
		glTranslatef(0, 0, -i);
	}
}

