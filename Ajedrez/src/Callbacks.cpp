// Callbacks.cpp | Source file for callback functions

#define STB_IMAGE_IMPLEMENTATION // Para la librería stb_image.h
#include "Callbacks.h"

#include <fstream>
#include <sstream>

// Cámara
Camara camara({ 0.0f, 172.0f, 135.0f }, { 0 });

// Modelos a renderizar
Modelo  rey_blanco(REY,  getPointFromCoords('e', 1),  "modelos/rey.obj", "texturas/marmol_blanco.jpg");
Modelo dama_blanca(DAMA, getPointFromCoords('d', 1), "modelos/dama.obj", "texturas/marmol_blanco.jpg");

Modelo   rey_negro(REY,  getPointFromCoords('e', 8),  "modelos/rey.obj",  "texturas/marmol_negro.jpg");
Modelo  dama_negra(DAMA, getPointFromCoords('d', 8), "modelos/dama.obj",  "texturas/marmol_negro.jpg");

std::vector<Modelo>  alfiles_blancos;
std::vector<Modelo> caballos_blancos;
std::vector<Modelo>   torres_blancas;
std::vector<Modelo>   peones_blancos;

std::vector<Modelo>   alfiles_negros;
std::vector<Modelo>  caballos_negros;
std::vector<Modelo>    torres_negras;
std::vector<Modelo>    peones_negros;

Modelo casillas_blancas(NONE, { 0, 0, 0 }, "modelos/casillas_blancas.obj", "texturas/marmol_blanco_oscuro.jpg");
Modelo casillas_negras (NONE, { 0, 0, 0 }, "modelos/casillas_negras.obj",  "texturas/marmol_negro_claro.jpg");

void motorGrafico(int* argc, char** argv)
{
	// Initialize GLUT and create a window
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutCreateWindow("FlatChess - ATdU, BBB, JBP, JNJP");

	inicializarEstadoOpenGL();
	inicializarIluminacion();

	// Set up the camera and viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	camara.update();
	registrarCallbacks();
	asignarModelos();
	cargarTexturas();

	glutMainLoop();
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
	glLightfv(GL_LIGHT0, GL_POSITION, camara.getLightPos());
	glLightfv(GL_LIGHT0, GL_AMBIENT,  camara.getLightAmb());
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  camara.getLightDif());
	glLightfv(GL_LIGHT0, GL_SPECULAR, camara.getLightSpe());
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
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

void asignarModelos(void)
{
	for (int i = 0; i < 8; i++)
	{
		peones_blancos.push_back(Modelo(PEON, getPointFromCoords('a' + i, 2), "modelos/peon.obj", "texturas/marmol_blanco.jpg"));
		 peones_negros.push_back(Modelo(PEON, getPointFromCoords('a' + i, 7), "modelos/peon.obj",  "texturas/marmol_negro.jpg"));
	}

	for (int i = 0; i < 2; i++)
	{
		 alfiles_blancos.push_back(Modelo(ALFIL,   getPointFromCoords('c' + i * 3, 1), "modelos/alfil.obj", "texturas/marmol_blanco.jpg"));
		  alfiles_negros.push_back(Modelo(ALFIL,   getPointFromCoords('c' + i * 3, 8), "modelos/alfil.obj",  "texturas/marmol_negro.jpg"));
		caballos_blancos.push_back(Modelo(CABALLO, getPointFromCoords('b' + i * 5, 1), "modelos/caballo.obj", "texturas/marmol_blanco.jpg"));
		 caballos_negros.push_back(Modelo(CABALLO, getPointFromCoords('b' + i * 5, 8), "modelos/caballo.obj",  "texturas/marmol_negro.jpg"));
		  torres_blancas.push_back(Modelo(TORRE,   getPointFromCoords('a' + i * 7, 1), "modelos/torre.obj", "texturas/marmol_blanco.jpg"));
		   torres_negras.push_back(Modelo(TORRE,   getPointFromCoords('a' + i * 7, 8), "modelos/torre.obj",  "texturas/marmol_negro.jpg"));
	}
}

void cargarTexturas(void)
{
     rey_blanco.cargarTextura();
	  rey_negro.cargarTextura();
	dama_blanca.cargarTextura();
	 dama_negra.cargarTextura();

	for (int i = 0; i < 2; i++)
	{
		alfiles_blancos[i].cargarTextura();
		 alfiles_negros[i].cargarTextura();
	   caballos_blancos[i].cargarTextura();
		caballos_negros[i].cargarTextura();
		 torres_blancas[i].cargarTextura();
		  torres_negras[i].cargarTextura();
	}

	for (int i = 0; i < 8; i++)
	{
		peones_blancos[i].cargarTextura();
		 peones_negros[i].cargarTextura();
	}

	casillas_blancas.cargarTextura();
	 casillas_negras.cargarTextura();
}

void renderizarModelos(void)
{
	 rey_blanco.render();
	  rey_negro.render();
	dama_blanca.render();
	 dama_negra.render();

	for (int i = 0; i < 2; i++)
	{
		alfiles_blancos[i].render();
		 alfiles_negros[i].render();
	   caballos_blancos[i].render();
		caballos_negros[i].render();
		 torres_blancas[i].render();
		  torres_negras[i].render();
	}

	for (int i = 0; i < 8; i++)
	{
		peones_blancos[i].render();
		 peones_negros[i].render();
	}

	casillas_blancas.render();
	 casillas_negras.render();
}

// Continuously draws what it is specified to it.
void OnDraw(void)
{
	renderizarModelos();
	glBegin(GL_POLYGON);
		glColor3ub(255, 0, 0);
		glTexCoord3d(2000, 0, 2000);
		glTexCoord3d(2000, 0, -2000);
		glTexCoord3d(-2000, 0, -2000);
		glTexCoord3d(-2000, 0, 2000);
	glEnd();
	glutSwapBuffers();
	glutPostRedisplay();

	// Camera update
	camara.update();

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
	camara.movement(0.025);

	glutTimerFunc(25, OnTimer, 0);
}

void OnKeyboardDown(const unsigned char key, int x_t, int y_t)
{
	switch (key)
	{
	case 'a':
		camara.setSpeed({ -50.0f, 0, 0 });
		break;
	case 'd':
		camara.setSpeed({ 50.0f, 0, 0 });
		break;
	case 's':
		camara.setSpeed({ 0, -50.0f, 0 });
		break;
	case 'w':
		camara.setSpeed({ 0, 50.0f, 0});
		break;
	case 'q':
		camara.setSpeed({ 0, 0, 50.0f });
		break;
	case 'e':
		camara.setSpeed({ 0, 0, -50.0f });
		break;
	default:
		break;
	}
}

void OnKeyboardUp(const unsigned char key, int x, int y)
{
	camara.setSpeed({ 0 });
	camara.printPosition(std::cout);

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