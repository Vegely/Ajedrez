// Callbacks.h | Header file for callback functions called by GLUT

#ifndef GLUTCALLBACKS_H
#define GLUTCALLBAKCS_H

#include "freeglut.h"
#include "Globals.h"

#include <string>
#include <iostream>
#include <vector>

/* INITIALIZATION */
void graphicsInit(int* argc, char** argv);

/* GLUT CALLBACKS */
void OnDraw(void);
void OnTimer(int value);
void OnReshape(int w, int h);
void OnMouseMotion(int x, int y);
void OnMouseClick(int button, int state, int x, int y);
void OnKeyboardDown(const unsigned char key, int x, int y);
void OnKeyboardUp(const unsigned char key, int x, int y);
void OnKeyboardSpecial(int key, int x, int y);

/* DEBUG AXIS */
void debugAxis(void);

/* ASSIMP FUNCTIONS */
void importModel(const char* file_path);
GLuint loadTexture(const std::string& file_path);

#endif
