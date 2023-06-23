// Callbacks.cpp | Source file for callback functions

#define STB_IMAGE_IMPLEMENTATION // Para la libreria stb_image.h
#include "Callbacks.h"
#include "CoordinadorAjedrez.h"

#include <fstream>
#include <sstream>

#include "ETSIDI.h"

// Coordinador
CoordinadorAjedrez coordinador;

void motorGrafico(int* argc, char** argv)
{
	// Inicializa GLUT y crea una ventana
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("FlatChess");

	registrarCallbacks();

	glEnable(GL_DEPTH_TEST);

	coordinador.init();

	glutMainLoop();
}

void registrarCallbacks(void)
{
	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutTimerFunc(1, OnTimer, 0);
	glutKeyboardFunc(OnKeyboardDown);
	glutKeyboardUpFunc(OnKeyboardUp);
	glutSpecialFunc(OnKeyboardSpecial);
	glutMouseFunc(OnMouseClick);
	glutPassiveMotionFunc(OnMouseMotion);
}

// Continuously draws what it is specified to it.
void OnDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	coordinador.Draw();

	glutSwapBuffers();
	//glutPostRedisplay();
}

// Reshapes the window if needed without resizing the objects and mantaining their proportions.
void OnReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

// Each set time, performs the set functions.
void OnTimer(int value)
{
	coordinador.Timer(0.001f);
	glutTimerFunc(1, OnTimer, 0);
}

void OnKeyboardDown(const unsigned char key, int x_t, int y_t)
{
	coordinador.Keypress(key);
}

void OnKeyboardUp(const unsigned char key, int x, int y)
{
	coordinador.Keylift(key);
}

void OnKeyboardSpecial(int key, int x, int y)
{
	coordinador.SpecialKeypress(key);
}

// 0 == left, 1 == middle, 2 == right, 3 == scroll up, 4 == scroll down.
void OnMouseClick(int button, int state, int x, int y)
{
	coordinador.Click(button, state, x, y);
	glutPostRedisplay();
}

void OnMouseMotion(int x, int y)
{

}