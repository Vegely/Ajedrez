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

	//inicializarIluminacion();
	//inicializarEstadoOpenGL();
	registrarCallbacks();

	glEnable(GL_DEPTH_TEST);

	coordinador.init();

	glutMainLoop();
}

void inicializarIluminacion(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat light0_position[] = { 0.0, 10.0, 0.0, 0.0 };
	GLfloat light_ambient[] = { 112, 112, 112, 1.0 };
	GLfloat light_diffuse[] = { 135, 135, 135, 1.0 };
	GLfloat light_specular[] = { 186, 186, 186, 1.0 };

	GLfloat materialAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat materialDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat materialShininess = 32.0f;

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

	//glClearColor(0.0, 0.0, 0.0, 0.0);
}

void inicializarEstadoOpenGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
}

void registrarCallbacks(void)
{
	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutTimerFunc(25, OnTimer, 0);
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
	coordinador.Timer(0.025f);
	glutTimerFunc(25, OnTimer, 0);
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