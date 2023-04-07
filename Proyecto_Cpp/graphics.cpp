#include "graphics.h"
#include "board.h"
#include "camera.h"
#include <string>
#include <iostream>

Board board({0, 0, 0}, 1.0f);
Camera player
(
	{ -5.0f, 10.0f, -5.0f },
	{ board.getCellLength() * 3.5f, board.getPosition().y, board.getCellLength() * 3.5f }
);

void init(int* argc, char* argv[], const char* windowName, int windowLength, int windowHeight)
{
	// Initialize window manager GLUT and create a window.
	glutInit(argc, argv);
	glutInitWindowSize(windowLength, windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(windowName);

	// Enable lights and define perspective.
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	// Callback registering.
	glutDisplayFunc(OnDraw);
	glutIdleFunc(OnDraw);
	glutReshapeFunc(OnReshape);
	glutTimerFunc(25, OnTimer, 0); // Each 25 ms, the function will call OnTimer(); 
	glutKeyboardFunc(OnKeyboardDown);
	glutMouseFunc(OnMouseClick);
	glutPassiveMotionFunc(OnMouseMotion);

	glutSetCursor(GLUT_CURSOR_NONE);

	// Pass control to GLUT, which will call the callbacks.
	glutMainLoop();
}

void OnReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void OnDraw(void)
{
	player.update();

	board.draw();
	player.lookAtTest();

	// End of drawing code (do not erase or write anything afterwards).
	glutSwapBuffers();
}

void OnTimer(int value)
{
	glTranslatef(player.getLookAt().x, player.getLookAt().y, player.getLookAt().z);
	player.animationRotate(10.0f, 10.0f, player.getLookAt());
	glTranslatef(-player.getLookAt().x, -player.getLookAt().y, -player.getLookAt().z);

	glutTimerFunc(value, OnTimer, 0); // Recalls the timer
	// End of timing code (do not erase or write anything afterwards).
	glutPostRedisplay();
}

void OnKeyboardDown(keypress key, int x_t, int y_t)
{
	player.keyboardMove(key, 1.0f);

	// End of keyboard reading code (do not erase or write anything afterwards).
	glutPostRedisplay();
}

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

	if (state == GLUT_DOWN)
	{
		std::cout << "Button: " << btn << std::endl;
		std::cout << "X:" << x << std::endl;
		std::cout << "Y:" << y << std::endl;
	}

	// End of mouse reading code (do not erase or write anything afterwards).
	glutPostRedisplay();
}

void OnMouseMotion(int x, int y)
{
	// End of mouse reading code (do not erase or write anything afterwards).
	glutPostRedisplay();
}