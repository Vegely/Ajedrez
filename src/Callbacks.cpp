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
	// Initialize GLUT and create a window
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("FlatChess");

	inicializarIluminacion();
	inicializarEstadoOpenGL();

	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);
	
	registrarCallbacks();

	coordinador.initGraficos();

	glutMainLoop();
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

// Reshapes the window if needed without resizing the objects and mantaining their proportions.
void OnReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection
	glLoadIdentity();
	gluPerspective(60.0f, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

// Continuously draws what it is specified to it.
void OnDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	coordinador.Draw();

	glutSwapBuffers();
	glutPostRedisplay();
}

// Each set time, performs the set functions.
void OnTimer(int value)
{
	coordinador.Timer(0.03);

	glutTimerFunc(30, OnTimer, 0);
}

void OnKeyboardDown(const unsigned char key, int x_t, int y_t)
{
	coordinador.Keypress(key);
}

void OnKeyboardUp(const unsigned char key, int x, int y)
{
	coordinador.Keylift(key);

	// End of keyboard reading code (do not erase or write anything afterwardas).
	//glutPostRedisplay();
}

void OnKeyboardSpecial(int key, int x, int y)
{
	coordinador.SpecialKeypress(key);

	// End of keyboard reading code (do not erase or write anything afterwardas).
	//glutPostRedisplay();
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

void inicializarEstadoOpenGL(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

void inicializarIluminacion(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);  
	//glEnable(GL_LIGHT2);  
	//glEnable(GL_LIGHT3);  
	//glEnable(GL_LIGHT4);
	//glEnable(GL_LIGHT5);
	//glEnable(GL_LIGHT6);
	//glEnable(GL_LIGHT7);

	// Light 0 properties (from above)
	GLfloat light0_position[] = { 1.0,  1.0,   1.0, 0.0 };
	GLfloat light1_position[] = { -1.0,  1.0,   1.0, 0.0 };
	GLfloat light2_position[] = { 1.0,  1.0,  -1.0, 0.0 };
	GLfloat light3_position[] = { -1.0,  1.0,  -1.0, 0.0 };
	GLfloat light4_position[] = { 1.0,  1.0,   1.0, 0.0 };
	GLfloat light5_position[] = { -1.0, -1.0,   1.0, 0.0 };
	GLfloat light6_position[] = { 1.0, -1.0,  -1.0, 0.0 };
	GLfloat light7_position[] = { -1.0, -1.0,  -1.0, 0.0 };

	GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	//glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	//glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	//glLightfv(GL_LIGHT3, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT3, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
	//glLightfv(GL_LIGHT4, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT4, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
	//glLightfv(GL_LIGHT5, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT5, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT6, GL_POSITION, light6_position);
	//glLightfv(GL_LIGHT6, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT6, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular);

	//glLightfv(GL_LIGHT7, GL_POSITION, light7_position);
	//glLightfv(GL_LIGHT7, GL_AMBIENT,  light_ambient);
	//glLightfv(GL_LIGHT7, GL_DIFFUSE,  light_diffuse);
	//glLightfv(GL_LIGHT7, GL_SPECULAR, light_specular);

	glClearColor(0.0, 0.0, 0.0, 0.0);
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