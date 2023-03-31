#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "freeglut.h"

using keypress = unsigned char;
using byte	   = unsigned char;

/* INITIALIZATION CODE */
void init(int* argc, char* argv[], const char* windowName, int windowLength, int windowHeight);

/* GLUT CALLBACKS */
void OnDraw(void);
void OnTimer(int value);
// Reshapes the window if needed without resizing the objects and mantaining their proportions.
void OnReshape(int w, int h);
void OnMouseMotion(int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnKeyboardDown(keypress key, int x, int y);

#endif
