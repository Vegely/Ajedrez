// Callbacks.cpp | Source file for callback functions

#define STB_IMAGE_IMPLEMENTATION // Para la librería stb_image.h
#include "Callbacks.h"

#include <fstream>
#include <sstream>

// Cámara
Camara camera({ 0.0f, 10.0f, 10.0f }, { 0 });
// Modelos a renderizar
Modelo rey1("modelos/rey.obj", "texturas/rocks.tga", REY);
Modelo rey2("modelos/rey.obj", "texturas/rocks.tga", REY);

void motorGrafico(int* argc, char** argv)
{
	// Initialize GLUT and create a window
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("FlatChess - ATdU, BBB, JBP, JNJP");

	// Set up the OpenGL state
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

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

	rey1.cargarTextura();
	rey2.cargarTextura();

	glutMainLoop();
}

// Continuously draws what it is specified to it.
void OnDraw(void)
{
	rey1.render(rey1.scene->mRootNode);
	glTranslatef(50, 0, 0);
	rey2.render(rey2.scene->mRootNode);
	glTranslatef(-50, 0, 0);

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