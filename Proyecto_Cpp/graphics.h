#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "tempObjects.h"

using keypress = unsigned char;
using byte	   = unsigned char;

/* INITIALIZATION CODE */
void init(int* argc, char* argv[], const char* windowName, int windowLength, int windowHeight);

/* GLUT CALLBACKS */
// Continuously draws what it is specified to it.
void OnDraw(void);
// Each set time, performs the set functions.
void OnTimer(int value);
// Reshapes the window if needed without resizing the objects and mantaining their proportions.
void OnReshape(int w, int h);
void OnMouseMotion(int x, int y);
// 0 == left, 1 == middle, 2 == right, 3 == scroll up, 4 == scroll down.
void OnMouseClick(int button, int state, int x, int y);
// Checks for a keyboard input. If it is pressed, updates the key value.
void OnKeyboardDown(keypress key, int x, int y);

#endif
