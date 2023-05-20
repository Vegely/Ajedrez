// Callbacks.cpp | Source file for callback functions called by GLUT

#include "Callbacks.h"
#include <vector>

// Global variables for the model data
std::vector<Model> models;

// Camera
Camera camera({ 0.0f, 10.0f, 10.0f }, { 0 });

void import_model(const char* file_path)
{
	// Create an instance of the Assimp importer and load the model file
	Assimp::Importer importer;
	GLuint model_list = 0;
	const aiScene* scene = importer.ReadFile(file_path,
		aiProcess_CalcTangentSpace		|
		aiProcess_Triangulate			|
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene)
	{
		std::cerr << "Failed to load model: " << importer.GetErrorString() << std::endl;
		return;
	}
	else
		std::cout << "Model loaded succesfully." << std::endl;

	// Creates a display list for the model
	model_list = glGenLists(1);
	glNewList(model_list, GL_COMPILE);

	// Traverses the scene graph and render each mesh
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		const aiMesh* mesh = scene->mMeshes[i];
		glBegin(GL_TRIANGLES);
		for (int j = 0; j < mesh->mNumFaces; j++)
		{
			const aiFace& face = mesh->mFaces[j];
			for (int k = 0; k < face.mNumIndices; k++)
			{
				const aiVector3D& vertex = mesh->mVertices[face.mIndices[k]];
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}
		}
		glEnd();
	}
	glEndList();

	models.push_back({ scene, model_list });
}

void graphicsInit(int* argc, char** argv)
{
	// Initialize GLUT and create a window
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("FlatChess");

	// Load the model file
	import_model("modelos/rey_blender.obj");
	import_model("modelos/teapot.obj");

	// Set up the OpenGL state
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	// Set up the camera and viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
		camera.getLookAt().x, camera.getLookAt().y, camera.getLookAt().z,
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
	glutPassiveMotionFunc(OnMouseMotion);

	glutMainLoop();
}

// Continuously draws what it is specified to it.
void OnDraw(void)
{
	for (int i = 0; i < models.size(); i++)
	{
		glTranslatef(i * 10, 0, 0);
			glCallList(models[i].model_list);
		glTranslatef(-i * 10, 0, 0);
	}

	glutSwapBuffers();
	glutPostRedisplay();

	// Camera update
	camera.update();

	// Debug axis
	debugAxis();
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
	camera.movement(0.025);

	glutTimerFunc(25, OnTimer, 0);
}

void OnKeyboardDown(const unsigned char key, int x_t, int y_t)
{
	switch (key)
	{
	case 'a':
		camera.setSpeed({ -10.0f, 0, 0 });
		break;
	case 'd':
		camera.setSpeed({ 10.0f, 0, 0 });
		break;
	case 's':
		camera.setSpeed({ 0, 0, 10.0f });
		break;
	case 'w':
		camera.setSpeed({ 0, 0, -10.0f });
		break;
	default:
		break;
	}
}

void OnKeyboardUp(const unsigned char key, int x, int y)
{
	camera.setSpeed({ 0 });

	// End of keyboard reading code (do not erase or write anything afterwardas).
	//glutPostRedisplay();
}

void OnKeyboardSpecial(int key, int x, int y)
{
	// End of keyboard reading code (do not erase or write anything afterwardas).
	//glutPostRedisplay();
}

// 0 == left, 1 == middle, 2 == right, 3 == scroll up, 4 == scroll down.
void OnMouseClick(int button, int state, int x, int y)
{
	static std::string btn;
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

