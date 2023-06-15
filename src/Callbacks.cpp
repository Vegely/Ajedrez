// Callbacks.cpp | Source file for callback functions

#define STB_IMAGE_IMPLEMENTATION // Para la librer�a stb_image.h
#include "Callbacks.h"
#include "Mundo.h"
#include "CoordinadorAjedrez.h"

#include <fstream>
#include <sstream>

#include "ETSIDI.h"

CoordinadorAjedrez ajedrez;

constexpr float fov_y = 60.0f;
int rotation = 180;

void motorGrafico(int* argc, char** argv)
{
	// Initialize GLUT and create a window
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("FlatChess - Adri�n Teixeira, Bogurad Bara�ski, Jorge Bengoa, Juan Nicol�s Jim�nez, Luis Miguel Muro");

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	registrarCallbacks();

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

// Continuously draws what it is specified to it.
void OnDraw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ajedrez.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();

}

// Reshapes the window if needed without resizing the objects and mantaining their proportions.
void OnReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection
	glLoadIdentity();
	gluPerspective(ajedrez.motorGrafico.getFovY(), (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

// Each set time, performs the set functions.
void OnTimer(int value)
{
	//ajedrez.motorGrafico.movimiento(0.03);
	//rotation++;
	glutTimerFunc(30, OnTimer, 0);
}

void OnKeyboardDown(const unsigned char key, int x_t, int y_t)
{
	ajedrez.tecla(key);
	//ajedrez.motorGrafico.keypress(key);
}

void OnKeyboardUp(const unsigned char key, int x, int y)
{
	//ajedrez.motorGrafico.keylift(key);

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
	//mundo.raycasting(button, state, x, y);
	//ajedrez.motorGrafico.seleccionCasilla(button, state, x, y);
	//std::cout << "X: " << x << std::endl;
	//std::cout << "Y: " << y << std::endl << std::endl;
	ajedrez.click(button,state,x,y);
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